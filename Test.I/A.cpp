struct IOWrapper {
private:
    handle_t _data;
public:
    ~IOWrapper() {
        if (_data != kNullHandle)
            raw_close(_data);
    }
    explicit IOWrapper(handle_t &&a) noexcept {
        _data = a;
        a = kNullHandle;
    }
    IOWrapper(IOWrapper &&a) noexcept {
        _data = a._data;
        a._data = kNullHandle;
    }
    IOWrapper& operator=(IOWrapper &&a) noexcept {
        _data = a._data;
        a._data = kNullHandle;
        return *this;
    }
    void Write(const std::string& content) {
        raw_write(_data, content);
    }
};
