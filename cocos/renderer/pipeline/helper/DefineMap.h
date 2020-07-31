#pragma once

#include "core/CoreStd.h"

namespace cc {
namespace pipeline {

class CC_DLL DefineMap final : public Object {
public:
    enum class ValueType {
        UNKNOW,
        NUMBER,
        BOOL,
        STRING
    };
    
    DefineMap() = default;

    template <class T>
    ENABLE_IF_T3(float, bool, String)
    getValue(const String &name) const {
        if (std::is_same<float, T>::value) {
            if (_numberMap.count(name) != 0) {
                return _numberMap.at(name);
            } else {
                CC_LOG_ERROR("Macro name: %s does't exist", name.c_str());
                return 0;
            }
        } else if (std::is_same<bool, T>::value) {
            if (_boolMap.count(name) != 0) {
                return _boolMap.at(name);
            } else {
                CC_LOG_ERROR("Macro name: %s does't exist", name.c_str());
                return false;
            }
        } else {
            if (_stringMap.count(name) != 0) {
                return _stringMap.at(name);
            } else {
                CC_LOG_ERROR("Macro name: %s does't exist", name.c_str());
                return String();
            }
        }
    }

    template <class T, class RET=void>
    ENABLE_IF_T3_RET(float, bool, String)
    setValue(const String &name, const T &value) {
        if (std::is_same<float, T>::value)
            _numberMap[name] = value;
        else if (std::is_same<bool, T>::value)
            _boolMap[name] = value;
        else
            _stringMap[name] = value;
    }
    
    ValueType getValueType(const String &name) const {
        if (_numberMap.count(name) != 0)
            return ValueType::NUMBER;
        else if (_boolMap.count(name) != 0)
            return ValueType::BOOL;
        else if (_stringMap.count(name) != 0)
            return ValueType::STRING;
        else
            return ValueType::UNKNOW;
    }

private:
    map<String, float> _numberMap;
    map<String, bool> _boolMap;
    map<String, String> _stringMap;
};

} // namespace pipeline
} // namespace cc
