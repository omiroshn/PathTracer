
#define	TwoPi  6.28318530717958648F

inline int   SolveP4Bi(float *x, float b, float d)
{
	float D = b * b - 4.0F * d;
	if( D >= 0.0F )
	{
		float sD = sqrt(D);
		float x1 = (-b + sD) / 2.0F;
		float x2 = (-b - sD) / 2.0F;
		if( x2 >= 0.0F )
		{
			float sx1 = sqrt(x1);
			float sx2 = sqrt(x2);
			x[0] = -sx1;
			x[1] =  sx1;
			x[2] = -sx2;
			x[3] =  sx2;
			return (4);
		}
		if( x1 < 0.0F )
		{
			float sx1 = sqrt(-x1);
			float sx2 = sqrt(-x2);
			x[0] =    0.0F;
			x[1] =  sx1;
			x[2] =    0.0F;
			x[3] =  sx2;
			return (0);
		}
			float sx1 = sqrt( x1);
			float sx2 = sqrt(-x2);
			x[0] = -sx1;
			x[1] =  sx1;
			x[2] =  0.0F;
			x[3] =  sx2;
			return (2);
	}
	else
	{
		float sD2 = 0.5F * sqrt(-D);
		float2 res = csqrt((float2){-0.5F * b, sD2});
		x[0] = res.x;
		x[1] = res.y;
		res = csqrt((float2){-0.5F * b,-sD2});
		x[2] = res.x;
		x[3] = res.y;
		return (0);
	}
}

inline float _root3 ( float x )
{
	float s = 1.0F;
	while ( x < 1.0F )
	{
		x *= 8.0F;
		s *= 0.5F;
	}
	while ( x > 8.0F )
	{
		x *= 0.125F;
		s *= 2.0F;
	}
	float r = 1.5F;
	r -= 1.0F / 3.0F * ( r - x / ( r * r ) );
	r -= 1.0F / 3.0F * ( r - x / ( r * r ) );
	r -= 1.0F / 3.0F * ( r - x / ( r * r ) );
	r -= 1.0F / 3.0F * ( r - x / ( r * r ) );
	r -= 1.0F / 3.0F * ( r - x / ( r * r ) );
	r -= 1.0F / 3.0F * ( r - x / ( r * r ) );
	return r * s;
}

inline float root3 ( float x )
{
	if ( x > 0.0F )
		return _root3 ( x );
	else
		if ( x < 0.0F )
			return -_root3 (-x);
		else
			return 0.0F;
}

inline int SolveP3(float *x,float a,float b,float c)
{
	float a2 = a * a;
	float q  = (a2 - 3.0F * b) / 9.0F;
	float r  = (a * (2.0F * a2 - 9.0F * b) + 27.0F * c) / 54.0F;
	float r2 = r * r;
	float q3 = q * q * q;
	float A,B;
	if (r2 <= (q3 + 1e-14F))
	{
		float t = r / sqrt(q3);
		if( t < -1.0F)
			t = -1.0F;
		if( t > 1.0F)
			t = 1.0F;
		t = acos(t);
		a /= 3.0F;
		q = -2.0F * sqrt(q);

		x[0] = q * cos(t / 3.0F) - a;
		x[1] = q * cos((t + TwoPi) / 3.0F) - a;
		x[2] = q * cos((t - TwoPi) / 3.0F) - a;
		return (3);
	}
	else
	{
		A = -root3(fabs(r) + sqrt(r2 - q3));
		if(r < 0.0F)
			A = -A;
		B = A == 0.0F ? 0.0F : q/A;

		a /= 3.0F;
		x[0] = (A + B) - a;
		x[1] = -0.5F * (A + B) - a;
		x[2] = 0.5F * sqrt(3.0F) * (A - B);
		if(fabs(x[2]) < 1e-14F)
		{
			x[2] = x[1];
			return (2);
		}
		return (1);
	}
}

inline void SWAP(float *a, float *b)
{
	float *t = b;
	b = a;
	a = t;
}

inline void  dblSort3( float *a, float *b, float *c) // make: a <= b <= c
{
	if( a > b )
		SWAP(a,b);	// now a<=b
	if( c < b )
	{
		SWAP(b,c);			// now a<=b, b<=c
		if( a > b )
			SWAP(a, b);// now a<=b
	}
}

inline int   SolveP4De(float *x, float b, float c, float d)
{
	if (fabs(c) < 1e-14F * (fabs(b) + fabs(d)))
		return SolveP4Bi(x,b,d);

	int res3 = SolveP3( x, 2.0F * b, b * b - 4.0F * d, -c * c);

	if( res3 > 1.0F )
	{
		dblSort3(&x[0], &x[1], &x[2]);

		if( x[0] > 0.0F)
		{
			float sz1 = sqrt(x[0]);
			float sz2 = sqrt(x[1]);
			float sz3 = sqrt(x[2]);

			if( c > 0.0F )
			{
				x[0] = (-sz1 -sz2 -sz3) / 2.0F;
				x[1] = (-sz1 +sz2 +sz3) / 2.0F;
				x[2] = (+sz1 -sz2 +sz3) / 2.0F;
				x[3] = (+sz1 +sz2 -sz3) / 2.0F;
				return 4;
			}
			x[0] = (-sz1 -sz2 +sz3) / 2.0F;
			x[1] = (-sz1 +sz2 -sz3) / 2.0F;
			x[2] = (+sz1 -sz2 -sz3) / 2.0F;
			x[3] = (+sz1 +sz2 +sz3) / 2.0F;
			return 4;
		}
		float sz1 = sqrt(-x[0]);
		float sz2 = sqrt(-x[1]);
		float sz3 = sqrt( x[2]);

		if( c > 0.0F )
		{
			x[0] = -sz3 / 2.0F;
			x[1] = ( sz1 -sz2) / 2.0F;
			x[2] =  sz3 / 2.0F;
			x[3] = (-sz1 -sz2) / 2.0F;
			return (0);
		}

		x[0] = sz3 / 2.0F;
		x[1] = (-sz1 +sz2) / 2.0F;
		x[2] = -sz3 / 2.0F;
		x[3] = ( sz1 +sz2) / 2.0F;
		return (0);
	}
	if (x[0] < 0.0F)
		x[0] = 0.0F;
	float sz1 = sqrt(x[0]);
	float szr, szi;
	float2 res = csqrt((float2){x[1], x[2]});
	szr = res.x;
	szi = res.y;
	if( c > 0 )
	{
		x[0] = -sz1 / 2.0F - szr;
		x[1] = -sz1 / 2.0F + szr;
		x[2] = sz1 / 2.0F;
		x[3] = szi;
		return (2);
	}

	x[0] = sz1 / 2.0F - szr;
	x[1] = sz1 / 2.0F + szr;
	x[2] = -sz1 / 2.0F ;
	x[3] = szi;
	return (2);
}

//-----------------------------------------------------------------------------
inline float N4Step(float x, float a, float b, float c, float d)
{
	float fxs= ((4.0F * x + 3.0F * a) * x + 2.0F * b) * x + c;
	if (fxs == 0.0F)
		return (x);
	float fx = (((x + a) * x + b) * x + c) * x + d;
	return (x - fx / fxs);
}
//-----------------------------------------------------------------------------

inline int   SolveP4(float *x, float a, float b, float c, float d)
{
	float d1 = d + 0.25F * a * ( 0.25F * b * a - 3.0F / 64.0F * a * a * a - c);
	float c1 = c + 0.5F * a * (0.25F * a * a - b);
	float b1 = b - 0.375F * a * a;
	int res = SolveP4De( x, b1, c1, d1);
	if( res == 4)
	{
		x[0]-= a / 4.0F;
		x[1]-= a / 4.0F;
		x[2]-= a / 4.0F;
		x[3]-= a / 4.0F;
	}
	else if (res==2)
	{
		x[0]-= a / 4.0F;
		x[1]-= a / 4.0F;
		x[2]-= a / 4.0F;
	}
	else
	{
		x[0]-= a / 4.0F;
		x[2]-= a / 4.0F;
	}

	if( res > 0 )
	{
		x[0] = N4Step(x[0], a,b,c,d);
		x[1] = N4Step(x[1], a,b,c,d);
	}

	if( res > 2 )
	{
		x[2] = N4Step(x[2], a,b,c,d);
		x[3] = N4Step(x[3], a,b,c,d);
	}
	return (res);
}
