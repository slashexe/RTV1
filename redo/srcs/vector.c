
#include "../../include/rtv1.h"

t_vertex	v_add(t_v3 v1, t_v3 v2)
{
	t_v3	vec;

	vec.x = v1.x + v2.x;
	vec.y = v1.y + v2.y;
	vec.z = v1.z + v2.z;
	return (vec);
}

t_v3		v_sub(t_v3 v1, t_v3 v2)
{
	t_v3	vec;

	vec = (t_v3){
		.x = v1.x - v2.x,
		.y = v1.y - v2.y,
		.z = v1.z - v2.z
	};
	return (vec);
}

float		v_dot(t_v3 v1, t_v3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_v3		v_mul_float(t_v3 v1, float f)
{
	t_v3	vec;

	vec = (t_v3){
		.x = v1.x * f,
		.y = v1.y * f,
		.z = v1.z * f
	};
	return (vec);
}