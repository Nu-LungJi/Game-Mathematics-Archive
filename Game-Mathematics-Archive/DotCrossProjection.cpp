#include <iostream>
#include <numbers>
#include <numeric>
struct Vector2D final {
    Vector2D() : X(0.f), Y(0.f) {}
    Vector2D(float x, float y) : X(x), Y(y) {}
    
    Vector2D operator-(const Vector2D& other) const {
        return {this->X - other.X, this->Y - other.Y};
    }
    Vector2D operator+(const Vector2D& other) const {
        return {this->X + other.X, this->Y + other.Y};
    }
    
    Vector2D operator*(const Vector2D& other) const {
        return {this->X * other.X, this->Y * other.Y};
    }
    Vector2D operator*(const float& param) const {
        return {this->X * param, this->Y * param};
    }
    
    Vector2D operator/(const Vector2D& other) const {
        return {this->X / other.X, this->Y / other.Y};
    }
    Vector2D operator/(const float& param) const {
        return {this->X / param, this->Y / param};
    }
    
    inline float Get_Distance() const { return std::sqrtf(X * X + Y * Y); }
    
    float X, Y;
};

struct Vector3D final {
    Vector3D() : X(0.f), Y(0.f), Z(0.f) {}
    Vector3D(float x, float y, float z) : X(x), Y(y), Z(z) {}
    
    Vector3D operator-(const Vector3D& other) const {
        return {this->X - other.X, this->Y - other.Y, this->Z - other.Z};
    }
    Vector3D operator+(const Vector3D& other) const {
        return {this->X + other.X, this->Y + other.Y, this->Z + other.Z};
    }
    
    Vector3D operator*(const Vector3D& other) const {
        return {this->X * other.X, this->Y * other.Y, this->Z * other.Z};
    }
    Vector3D operator*(const float& param) const {
        return {this->X * param, this->Y * param, this->Z * param};
    }
    
    Vector3D operator/(const Vector3D& other) const {
        return {this->X / other.X, this->Y / other.Y, this->Z / other.Z};
    }
    Vector3D operator/(const float& param) const {
        return {this->X / param, this->Y / param, this->Z / param};
    }
    
    inline float Get_Distance() const { return std::sqrtf(X * X + Y * Y + Z * Z); }
    inline void  Print_Element() const { std::cout << "{ " << X << ", " << Y << ", " << Z << "}" << '\n'; }
    
    float X, Y, Z;
};

struct Observer {
    Vector2D Position = {0.f, 0.f };
    Vector2D Forward  = { 1.f, 0.f };
    float ViewDegree = 90;
    
    bool IsOnView(Vector2D Pos) {
        float Radian = ViewDegree * std::numbers::pi / 180.f;
        
        // std::cout << "Observer ViewAngle : " << "-" << Radian / 2.f << " ~ +" << Radian / 2.f << '\n';
        
        float OtherRadian = std::atan2(Pos.Y, Pos.X);
        // std::cout << "Other's Angle : " << OtherRadian << '\n';
        
        if (OtherRadian > Radian / 2.f || OtherRadian < Radian / -2.f) {
            // std::cout << "Other is Out of View" << '\n';
            return false;
        }
        
        // std::cout << "Other is in View" << '\n';
        return true;
    }
};

float DotProduct(Vector3D Vec1, Vector3D Vec2) {
    return Vec1.X * Vec2.X + Vec1.Y * Vec2.Y +Vec1.Z * Vec2.Z;
}
float DotProduct(Vector2D Vec1, Vector2D Vec2) {
    return Vec1.X * Vec2.X + Vec1.Y * Vec2.Y;
}

Vector3D CrossProduct(Vector3D Vec1, Vector3D Vec2) {
    return { Vec1.Y * Vec2.Z - Vec1.Z * Vec2.Y, Vec1.Z * Vec2.X - Vec1.X * Vec2.Z, Vec1.X * Vec2.Y - Vec1.Y * Vec2.X };
}
float CrossProduct(Vector2D Vec1, Vector2D Vec2) {
    return { Vec1.X * Vec2.Y - Vec1.Y * Vec2.X };
}

Vector2D Normalize(Vector2D Vec) {
    return Vec / Vec.Get_Distance();
}
Vector3D Normalize(Vector3D Vec) {
    return Vec / Vec.Get_Distance();
}

void Simulator() {
    
    // Day 3
    {
        Observer Obs;
    
        float Epsilon = FLT_EPSILON;
        
        Vector2D TargetPosA = { 1.f, 1.f };
        Vector2D TargetPosB = { 10.f, 10.f };
        
        float ResultA = DotProduct(Normalize(TargetPosA - Obs.Position), Normalize(Obs.Forward));
        float ResultB = DotProduct(Normalize(TargetPosB - Obs.Position), Normalize(Obs.Forward));
        
        float Threshold = std::cosf(Obs.ViewDegree / 2.f * std::numbers::pi / 180.f);
        
        if (ResultA >= Threshold - Epsilon) std::cout << "true" << '\n';
        if (ResultB >= Threshold - Epsilon) std::cout << "true" << '\n';
    }
    
    // Day 4
    {
        Vector3D TargetA = { 0.f, 0.f, 0.f };
        Vector3D TargetB = { 1.f, 0.f, 0.f };
        Vector3D TargetC = { 0.f, 0.f, 1.f };
        
        Vector3D AtoB = TargetB - TargetA;
        Vector3D BtoC = TargetC - TargetB;
        
        Vector3D Result = Normalize(CrossProduct(AtoB, BtoC));
        Result.Print_Element();
    }
    
    // Day 5
    {
        Vector3D TargetA = { 0.f, 0.f, 0.f };
        Vector3D TargetB = { 1.f, 0.f, 0.f };
        Vector3D TargetC = { 0.f, 0.f, 1.f };
        
        Vector3D AtoB = TargetB - TargetA;
        Vector3D BtoC = TargetC - TargetB;
        
        Vector3D ResultA = Normalize(CrossProduct(AtoB, BtoC));
        ResultA.Print_Element();
        
        Vector3D AtoC = TargetC - TargetA;
        Vector3D CtoB = TargetB - TargetC;
        
        Vector3D ResultB = Normalize(CrossProduct(AtoC, CtoB));
        ResultB.Print_Element();
        
        float FinalResult = DotProduct(ResultA, ResultB);
        std::cout << "Final Result : " << FinalResult << '\n';
    }
    
    // Day 6
    {
        Vector2D OuterNormal = { 1.f, 0.f };
        Vector2D SpeedA = { -3.f, 4.f };
        Vector2D SpeedB = { 3.f, 4.f };
        
        float SpeedA_Result = DotProduct(OuterNormal, SpeedA);
        float SpeedB_Result = DotProduct(OuterNormal, SpeedB);
        
        if (SpeedA_Result < 0) SpeedA = SpeedA - OuterNormal * SpeedA_Result;
        if (SpeedB_Result < 0) SpeedB = SpeedB - OuterNormal * SpeedB_Result;
        
        std::cout << "Current Speed of (-3, 4) is (" << SpeedA.X << ", " << SpeedA.Y << ")" << '\n';
        std::cout << "Current Speed of (3, 4) is (" << SpeedB.X << ", " << SpeedB.Y << ")" << '\n';
    }
}

int main() {
    Simulator();
    return 0;
}