#ifndef RANDOM_H
#define RANDOM_H

class linearGen32 {
        unsigned long _x;
        unsigned long _a;
        unsigned long _c;
        unsigned long _m;
public:
        linearGen32()
        : _x(13UL),
          _a(2147483629UL),
          _c(2147483587UL),
          _m(4294967291UL) {}

        linearGen32(unsigned long t_x)
        : _x(t_x),
          _a(2147483629UL),
          _c(2147483587UL),
          _m(4294967291UL) {}

        unsigned long operator()()
        {
                _x = (_a*_x + _c)%_m;
                return _x;
        }
};

class linearGen64 {
        unsigned long long _x;
        unsigned long long _a;
        unsigned long long _c;
        unsigned long long _m;
public:
        linearGen64()
        : _x(13ULL),
          _a(6364136223846793005ULL),
          _c(1442695040888963407ULL),
          _m(18446744073709551615ULL) {}

        linearGen64(unsigned long long t_x)
        : _x(t_x),
          _a(6364136223846793005ULL),
          _c(1442695040888963407ULL),
          _m(18446744073709551615ULL) {}

        unsigned long long operator()()
        {
                _x = (_a*_x + _c)%_m;
                return _x;
        }
};

class splitmixGen32 {
        unsigned long _state;
public:
        splitmixGen32()
        : _state(65537UL) {}

        splitmixGen32(unsigned long t_state)
        : _state(t_state) {}

        unsigned long operator()()
        {
                unsigned long long result = _state;
                _state = result + 0x9E3779B97f4A7C15ULL;
                result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9ULL;
                result = (result ^ (result >> 27)) * 0x94D049BB133111EBULL;
                return ((result ^ (result >> 31)) >> 32);
        }
};

class splitmixGen64 {
        unsigned long _state;
public:
        splitmixGen64()
        : _state(6578965829ULL) {}

        splitmixGen64(unsigned long t_state)
        : _state(t_state) {}

        unsigned long operator()()
        {
                unsigned long long result = _state;
                _state = result + 0x9E3779B97f4A7C15ULL;
                result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9ULL;
                result = (result ^ (result >> 27)) * 0x94D049BB133111EBULL;
                return result ^ (result >> 31);
        }
};

class xorshiftGen32 {
        unsigned long _state;
public:
        xorshiftGen32()
        : _state(splitmixGen32(9285698767UL)()) {}

        xorshiftGen32(unsigned long t_state)
        : _state(splitmixGen32(t_state)()) {}

        unsigned long operator()()
        {
                _state ^= _state << 13;
                _state ^= _state >> 17;
                _state ^= _state << 5;
                return _state;
        }
};

class xorshiftGen64 {
        unsigned long _state;
public:
        xorshiftGen64()
        : _state(splitmixGen64(49106107369113ULL)()) {}

        xorshiftGen64(unsigned long long t_state)
        : _state(splitmixGen64(t_state)()) {}

        unsigned long operator()()
        {
                _state ^= _state << 13;
                _state ^= _state >> 17;
                _state ^= _state << 5;
                return _state;
        }
};

#endif //RANDOM_H
