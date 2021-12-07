#include <iostream>
#include <set>
#include <random>

using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::vector;
using std::string;
using std::default_random_engine;
using std::uniform_int_distribution;

class State{
public:
    virtual bool contains(int s) const = 0;
private:
};

class DiscreteState : public State {
private:
    const int state;

public:
    explicit DiscreteState(int state) : state(state) {}

    bool contains(int s) const override {
        return s == state;
    }
};

class SegmentState : public State {
private:
    int const beg, end;

public:
    SegmentState() : beg(0), end(-1) { }
    SegmentState(int beg, int end) : beg(beg), end(end) { }

    bool contains(int s) const override{
        return s >= beg && s <= end;
    }
};

class SetState : public State {
private:
    set<int> const states;

public:
    SetState() : states() { }
    explicit SetState(set<int> const &src) : states(src) { }

    bool contains(int s) const override {
        return states.count(s) > 0;
    }
};

class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count) : seed(seed), test_min(test_min), test_max(test_max), test_count(test_count) { }

    float operator()(State const &s) const {
        default_random_engine rng(seed);
        uniform_int_distribution<int> dstr(test_min, test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;

        return static_cast<float>(good) / static_cast<float>(test_count);
    }


};

class Intersection : public State {

public:
    State& State1;
    State& State2;

    bool contains(int s) const override {
        return (State1.contains(s) && State2.contains(s));
    }
    Intersection(State& state1, State& state2) : State1(state1), State2(state2) {}
private:

};

class Association : public State {

public:
    State& State1;
    State& State2;

    bool contains(int s) const override {
        return (State1.contains(s) || State2.contains(s));
    }
    Association(State& state1, State& state2) : State1(state1), State2(state2) {}
private:

};


int main(int argc, const char * argv[]) {
    DiscreteState d(1);
    SegmentState s(0, 10);
    SetState ss({ 1, 3, 5, 7, 23, 48, 57, 60, 90, 99 });
    Intersection inter(d, s);
    Association assoc(d, s);
    ProbabilityTest pt(10, 0, 100, 100000);
    for (int i = 100;i < 1000000; i += 10000)
    {
        ProbabilityTest pt(10, 0, 100, i);
        cout << pt(d)<< endl;
    }
    cout << pt(d) << endl;
    cout << pt(s) << endl;
    cout << pt(ss) << endl;
    return 0;
}
