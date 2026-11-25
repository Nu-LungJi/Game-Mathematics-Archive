    #include <algorithm>
    #include <iostream>
    #include <math.h>

    inline constexpr float PI = 3.141592f;

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


    float DegreeToRadian(const float& Degree) {
        return Degree / 180.f * PI;
    }

    float RadianToDegree(const float& Radian) {
        return Radian / PI * 180.f;
    }

    Vector2D Get_Coordinate(const float& Degree, const float& Length, Vector2D Start = {0.f, 0.f}) {
        float Radian = DegreeToRadian(Degree);
        return { Start.X + std::cosf(Radian) * Length, Start.Y + std::sinf(Radian) * Length };
    }

    void Print_Coordinate(const Vector2D& Coord) {
        std::cout << "Coordinate : { " << Coord.X << ", " << Coord.Y << " }" << '\n'; 
    }

    float Get_Degree(Vector2D Start, Vector2D Target) {
        Vector2D Direction = Target - Start;
        return RadianToDegree(std::atan2f(Direction.Y, Direction.X));
    }

    float Get_MinimumDegree(Vector2D Vec1, Vector2D Vec2) {
        float Diff = RadianToDegree(std::atan2f(Vec2.Y, Vec2.X)) - RadianToDegree(std::atan2f(Vec1.Y, Vec1.X));
        if (Diff > 180.f) Diff -= 360.f;
        else if (Diff <= -180.f) Diff += 360.f;
        
        return Diff;
    }

    float Normalize_Degree(float Degree)
    {
        Degree = std::fmod(Degree, 360.f);

        if (Degree < 0.f) Degree += 360.f;

        return Degree;
    }

    int main() {
        // Day 3
        {
            constexpr float Angle = 30.f;
            constexpr float Length = 2.f;
            Vector2D StartPoint = { 1.f, 1.f };
        
            Print_Coordinate(Get_Coordinate(Angle, Length, StartPoint));
        }
        
        // Day 4
        {
            float StartDeg  = Get_Degree({2.f, 1.f}, {2.f, 4.f});
            float EndDeg    = Get_Degree({2.f, 1.f}, {-1.f, 1.f});
        
            std::cout << "Start Degree : " << StartDeg << ", End Degree : " << EndDeg << '\n';
            std::cout << "Rotation Result : " << EndDeg - StartDeg << '\n';
        }
        
        // Day 5
        {
            Vector2D Start  = Get_Coordinate(-10, 1, {0.f, 0.f});
            Vector2D End    = Get_Coordinate(10, 1, {0.f, 0.f});
            
            std::cout << "Start : { " << Start.X << ", " << Start.Y << " }" << ", End : { " << End.X << ", " << End.Y << " }" << '\n';
            std::cout << "Rotation Result : " << Get_MinimumDegree(Start, End) << '\n';
        }
        {
            Vector2D Start  = Get_Coordinate(10, 1, {0.f, 0.f});
            Vector2D End    = Get_Coordinate(350, 1, {0.f, 0.f});
            
            std::cout << "Start : { " << Start.X << ", " << Start.Y << " }" << ", End : { " << End.X << ", " << End.Y << " }" << '\n';
            std::cout << "Rotation Result : " << Get_MinimumDegree(Start, End) << '\n';
        }
        
        // Day 6
        {
            int FrameCount = 4;
            
            float StartAngle = -350.f, EndAngel = 10.f;
            
            Vector2D Start  = Get_Coordinate(StartAngle, 1);
            Vector2D End    = Get_Coordinate(EndAngel, 1);
            
            float MaxMovementAmount = Get_MinimumDegree(Start, End);
            bool isPositive = MaxMovementAmount >= 0.f;
            float CurMovementAmount = 0.f;
            
            constexpr float SpeedAngle = 60.f;
            constexpr float DeltaTime = 0.1f;
            
            float DeltaAngle = SpeedAngle * DeltaTime * (isPositive ? 1.f : -1.f);
                
            while (FrameCount--) {
                CurMovementAmount += DeltaAngle;
                if ((isPositive && CurMovementAmount > MaxMovementAmount) || (!isPositive && CurMovementAmount < MaxMovementAmount)) 
                    CurMovementAmount = MaxMovementAmount;
                
                float Result = StartAngle + CurMovementAmount; 
                Result = Normalize_Degree(Result);
                std::cout << Result << " ";
            }
        }
        return 0;
    }