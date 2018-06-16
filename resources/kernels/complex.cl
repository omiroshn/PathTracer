inline float cmod(float2 a){
    return (sqrt(a.x*a.x + a.y*a.y));
}

inline float carg(float2 a){
    if(a.x > 0)
        return atan(a.y / a.x);
    else if(a.x < 0 && a.y >= 0)
        return atan(a.y / a.x) + M_PI;
    else if(a.x < 0 && a.y < 0)
        return atan(a.y / a.x) - M_PI;
    else if(a.x == 0 && a.y > 0)
        return M_PI/2;
    else if(a.x == 0 && a.y < 0)
        return -M_PI/2;
    else
        return 0;
}

inline float2  cmult(float2 a, float2 b)
{
    return (float2)( a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x);
}

inline float2 cdiv(float2 a, float2 b)
{
    return (float2)((a.x*b.x + a.y*b.y)/(b.x*b.x + b.y*b.y), (a.y*b.x - a.x*b.y)/(b.x*b.x + b.y*b.y));
}

inline float2 csqrt(float2 a)
{
    return (float2)( sqrt(cmod(a)) * cos(carg(a)/2),  sqrt(cmod(a)) * sin(carg(a)/2));
}
