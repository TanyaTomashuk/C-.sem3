#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
 
// Electromagnetic interaction
// You have to create world and be able to add and delete particles from it
// When you add or delete particle you must recalculate all interactions
 
// Требуется описать мир с некоторыми частицами
// Координата/скорость задается через структуру vector3
 
struct vector3;
vector3 operator*(const vector3& v1, double d);
 
struct vector3 {
    double x;
    double y;
    double z;
 
    double abs() {
        return sqrt(x * x + y * y + z * z);
    }
 
    vector3 unit() {
        vector3 u = *this;
        u *= 1.0 / abs();
        return u;
    }
 
    vector3& operator+=(const vector3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
 
    vector3& operator-=(const vector3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
 
    vector3& operator*=(double d) {
        x *= d;
        y *= d;
        z *= d;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream&, const vector3&);
};
 
vector3 operator+(const vector3& v1, const vector3& v2) {
    vector3 v = v1;
    v += v2;
    return v;
}
 
vector3 operator-(const vector3& v1, const vector3& v2) {
    vector3 v = v1;
    v -= v2;
    return v;
}
 
vector3 operator*(const vector3& v1, double d) {
    vector3 v = v1;
    v *= d;
    return v;
}
 
std::ostream& operator<<(std::ostream& os, const vector3& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}
 
// Для описания событий происходящих в мире напишите свой небольшой логгер, который умеет
// Запоминать создание, изменение и уничтожение частиц
 
class Logger {
public:
    Logger() = default;
    void log(const std::string& s) {
        std::ostringstream oss;
        oss << "[" << l.size() + 1 << "] ";
        l.push_back(oss.str() + s);
    }
 
    void display() {
        for (int i = 0; i != l.size(); i++)
            std::cout << l[i] << "\n";
    }
 
    ~Logger() = default;
private:
    std::vector<std::string> l;
};
 
// Существует базовый класс частиц, который внутри себя хранит информацию о частице
// Допишите этот родительский класс так, чтобы он мог считать количество объектов, созданных от него
 
class Particle;
std::ostream& operator<<(std::ostream& os, const Particle& p);
 
class Particle {
protected:
    // Поля, описывающие частицу
    // Можно дописать свои
    double mass = 0;
    double charge = 0;
    vector3 coordinate = { 0, 0, 0 };
    vector3 velocity = { 0, 0,0 };
    vector3 force = { 0, 0, 0 };
    double energy = 0;
    std::string name;
    int index = -1;
    std::string type = "Particle";
    // Логгер для записи событий
    Logger logger;
 
public:
    Particle() = default;
 
    // explicit Particle(double energy);
    explicit Particle(double charge, double mass, vector3 coordinate, vector3 velocity = { 0, 0, 0 }, std::string type = "Particle") :
        charge(charge),
        mass(mass),
        coordinate(coordinate),
        velocity(velocity),
        type(type)
    {
        std::ostringstream oss;
        oss << "created as " << *this;
        logger.log(oss.str());
    }
    
    // метод, который вам необходимо переопределить в дочерних классах
    // см. или вспомнить лекцию
    // внутри него напишите логику взаимодействия двух частиц (например, кулоновское)
    void clearInteraction() {
        force = { 0, 0, 0 };
        energy = 0;
        logger.log("cleared interaction");
    }
 
    virtual void interaction(Particle const& p) {
        std::ostringstream oss;
        oss << "interacted with particle with index == " << p.getIndex();
        logger.log(oss.str());
 
        vector3 dist = coordinate - p.coordinate;
        const double k = 8.9875 * 10e9;
        vector3 delta = dist.unit() * (k * charge * p.charge * pow(dist.abs(), -2.0));
        force += delta;
        energy += k * charge * p.charge / dist.abs();
    }
 
    void displayLog() {
        std::cout << "Log of particle (" << index << "):\n";
        logger.display();
        logger.log("displayed log");
    }
 
    // Геттеры
 
    int getIndex() const {
        return index;
    }
 
    std::string getType() const {
        return type;
    }
 
    std::string getName() const {
        return name;
    }
 
    double getEnergy() const {
        return energy;
    }
 
    double getMass() const {
        return mass;
    }
 
    double getCharge() const {
        return charge;
    }
 
    vector3 getCoordinate() const {
        return coordinate;
    }
 
    vector3 getVelocity() const {
        return velocity;
    }
 
    vector3 getForce() const {
        return force;
    }
 
    vector3 getAcceleration() const {
        return force * (1 / mass);
    }
 
    // Сеттеры
 
    void setIndex(int i) {
        index = i;
    }
 
    void setMass(double d) {
        mass = d;
    }
 
    void setCharge(double d) {
        charge = d;
    }
 
    void setCoordinate(vector3 v) {
        coordinate = v;
    }
 
    void setVelocity(vector3 v) {
        velocity = v;
    }
 
    virtual ~Particle() = default;
};
 
std::ostream& operator<<(std::ostream& os, const Particle& p) {
    os << "(" << p.getIndex() << ") " <<  p.getType() << " [q = " << p.getCharge() << ", m = " << p.getMass() 
        << ", r = " << p.getCoordinate() << ", v = "  << p.getVelocity() << ", a = " << p.getAcceleration() 
        << ", F = " << p.getForce() << ", W = " << p.getEnergy() << "]";
    
    return os;
}
 
 
// описать несколько классов разных частиц
// например такой
class Electron : public Particle {
public:
    // в этом конструкторе предлагается задавать координаты и через энергию остальные параметры частицы
    // только это по ряду причин невозможно
    // explicit Electron(double energy, vector3 coords) {
 
    // }
 
    explicit Electron(vector3 coordinate, vector3 velocity = { 0, 0, 0 }) :
        Particle(-1.602 * 10e-19, 9.109 * 10e-31, coordinate, velocity, "Electron")
    {
 
    }
 
    // interaction не нуждается в переопределении
    // void interaction(Particle& p) override;
    virtual ~Electron() = default;
};
 
 
class Proton : public Particle {
public:
    explicit Proton(vector3 coordinate, vector3 velocity = { 0, 0, 0 }) :
        Particle(1.602 * 10e-19, 1.673 * 10e-27, coordinate, velocity, "Proton")
    {
 
    }
 
    virtual ~Proton() = default;
};
 
 
class Neutron : public Particle {
public:
    explicit Neutron(vector3 coordinate, vector3 velocity = { 0, 0, 0 }) :
        Particle(0, 1.675 * 10e-27, coordinate, velocity, "Neutron")
    {
 
    }
 
    virtual ~Neutron() = default;
};
 
// в этом классе опишите мир, состоящий из некоторого числа частиц
class World {
    std::vector<Particle> v;
    int index = 0;
    
public:
    void recalculate() {
        for (int i = 0; i != v.size(); i++)
            v[i].clearInteraction();
 
        for (int i = 0; i != v.size(); i++)
            for (int j = 0; j != v.size(); j++) {
                if (i == j)
                    continue;
 
                v[i].interaction(v[j]);
            }
    }
 
    // добавить частицу в мир (она должна провзаимодействовать со всеми остальными)
    // возвращает индекс
    int addParticle(const Particle& p) {
        Particle copy = p;
        copy.setIndex(index);
        index++;
        v.push_back(copy);
 
        recalculate();
 
        return index - 1;
    }
    // удалить частицу из мира
    void deleteParticle(int index) {
        for (int i = 0; i != v.size(); i++) {
            if (v[i].getIndex() == index) {
                v.erase(v.begin() + i);
 
                recalculate();
                return;
            }
        }
    }
 
    void displayLog() {
        for (int i = 0; i != v.size(); i++) {
            v[i].displayLog();
            std::cout << "\n";
        }
    }
 
    friend std::ostream& operator<<(std::ostream&, const World&);
};
 
// перегрузите оператор вывода, чтобы можно было вывести состав мира
// (может потребоваться перегрузка оператора вывода для частиц)
std::ostream& operator<<(std::ostream& os, const World& w) {
    for (int i = 0; i != w.v.size(); i++)
        os << w.v[i] << "\n";
    
    return os;
}
 
// здесь создайте мир/миры, куда добавьте некоторое число частиц, взаимодействующих друг с другом
int main() {
    // Тесты
    World w;
    int electron = w.addParticle(Electron({-1, 0, 0}));
    int proton = w.addParticle(Proton({1, 0, 0}));
    std::cout << w << "\n\n";
 
    int neutron = w.addParticle(Neutron({0, 0, 0}));
    std::cout << w << "\n\n";
    w.displayLog();    
 
    w.deleteParticle(proton);
    std::cout << w << "\n\n";
    w.displayLog();
 
    w.deleteParticle(neutron);
    std::cout << w << "\n\n";
 
    w.deleteParticle(electron);
    std::cout << w << "\n\n";    
}
