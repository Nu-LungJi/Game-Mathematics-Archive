#include <iostream>

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

Vector2D Displacement(Vector2D Start, Vector2D End, float Distance) {
    Vector2D Vector = End - Start;
    Vector2D UnitVec = Vector / Vector.Get_Distance();
    return Start + UnitVec * Distance;
}

//Vector2D MoveTowards(Vector2D Start, Vector2D End, float Velocity, float dt) {
//    Vector2D Vector = End - Start;
//    Vector2D UnitVec = Vector / Vector.Get_Distance();
//    
//    return Start + UnitVec * Velocity * dt;
//}

float MovementDistance(Vector2D Start, Vector2D End, float Velocity, float dt) {
    Vector2D Vector = End - Start;
    Vector2D UnitVec = Vector / Vector.Get_Distance();
    Vector2D Result = UnitVec * Velocity * dt;
    
    return Result.Get_Distance();
}

Vector2D MoveTowards(Vector2D Start, Vector2D End, float Velocity, float dt) {
    Vector2D Vector = End - Start;
    
    float Distance = Vector.Get_Distance();
    if (Distance == 0.f) return End;
    
    Vector2D UnitVec = Vector / Distance;
    float Movement = Velocity * dt;
    
    return Distance <= Movement ? End : Start + UnitVec * Movement;
}

int main() {
    Vector2D Start = {0.f, 0.f};
    Vector2D End = {0.3f, 0.4f};

    float Speed = 2.f;
    float DT = 1.f;

    Vector2D First = MoveTowards(Start, End, Speed, DT);
    Vector2D Second = MoveTowards(First, End, Speed, DT);

    return 0;
    //Vector2D Result = MoveTowards(Start, End, Speed, DT);
    //std::cout << "CurPost : { " << Result.X << ", " << Result.Y << " }" << ", Speed : " << Speed << "m/s"
    //    << ", DeltaTime : " << DT << "\n"; 
    //
    //DT = 0.25f;
    //Vector2D CurPos = Start;
    //for (int i = 0; i < 4; ++i) {
    //    CurPos = MoveTowards(CurPos, End, Speed, DT);
    //    
    //    std::cout << "CurPost : { " << CurPos.X << ", " << CurPos.Y << " }" << ", Speed : " << Speed << "m/s"
    //        << ", DeltaTime : " << DT << "\n"; 
    //}

    for (int i = 0; i < 4; ++i) {
        Vector2D Result = MoveTowards(Start, End, Speed, DT * (i + 1));
        std::cout << "CurPost : { " << Result.X << ", " << Result.Y << " }" << ", Speed : " << Speed << "m/s"
            << ", DeltaTime : " << DT << "\n";

        Start = Result;
    }
    
    return 0;
}