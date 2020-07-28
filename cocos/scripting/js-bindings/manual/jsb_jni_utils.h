
#pragma once

#include <sstream>
#include <string>
#include <vector>
#include "jni.h"

namespace JniUtils {
    enum class JniTypeEnum : uint8_t {
        None,
        Void_V,
        Boolean_Z,
        Char_C,
        Short_S,
        Byte_B,
        Int_I,
        Long_J,
        Float_F,
        Double_D,
        Object_L,
        MAX_TYPE
    };

    struct JniType {
        int dim = 0;
        JniTypeEnum type = JniTypeEnum::None;
        std::string klassName;

        JniType() = default;

        JniType(const JniType &o) {
            type = o.type;
            dim = o.dim;
            klassName = o.klassName;
        }

        JniType(JniType &&other) {
            this->dim = other.dim;
            this->type = other.type;
            this->klassName = std::move(other.klassName);
            other.dim = 0;
            other.type = JniTypeEnum::None;
        }
        JniType& operator = (const JniType &o) {
            type = o.type;
            dim = o.dim;
            klassName = o.klassName;
            return *this;
        }

        JniType rankDec() const {
            JniType b(*this);
            b.dim -= 1;
            return b;
        }

        static JniType from(JniTypeEnum e);

        static JniType fromString(const std::string &name);

        static std::string reparse(const std::string &);

        std::string toString() const;

        inline bool isNone() const { return type == JniTypeEnum::None; }

        inline bool isVoid() const { return type == JniTypeEnum::Void_V; }

        inline bool isBoolean() const { return type == JniTypeEnum::Boolean_Z; }

        inline bool isChar() const { return type == JniTypeEnum::Char_C; }

        inline bool isShort() const { return type == JniTypeEnum::Short_S; }

        inline bool isByte() const { return type == JniTypeEnum::Byte_B; }

        inline bool isInt() const { return type == JniTypeEnum::Int_I; }

        inline bool isLong() const { return type == JniTypeEnum::Long_J; }

        inline bool isFloat() const { return type == JniTypeEnum::Float_F; }

        inline bool isDouble() const { return type == JniTypeEnum::Double_D; }

        inline bool isObject() const { return type == JniTypeEnum::Object_L; }

        inline bool isMAX() const { return type == JniTypeEnum::MAX_TYPE; }

        inline const std::string &getClassName() const { return klassName; }
    };

    std::vector<JniUtils::JniType>
    exactArgsFromSignature(const std::string &signature, bool &success);

    bool parseSigType(const char *data, size_t max_length, size_t *len,
                      JniType *type);
} // namespace jni_utils
