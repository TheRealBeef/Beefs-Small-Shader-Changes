#ifndef	MBLUR_H
#define MBLUR_H

#ifndef 	USE_MBLUR
float3 	mblur	(float2 UV, float3 pos, float3 c_original)	{ return c_original; }
#else

#include "common.h"
////////////////////////////////////////
uniform float4x4	m_current;
uniform float4x4	m_previous;
uniform float2 	m_blur;	
uniform Texture2D s_blur;
////////////////////////////////////////

float3 	mblur	(float2 UV, float3 pos, float3 c_original)	
{
	pos.z   +=		(saturate(0.001 - pos.z)*10000.h);

	float4 	pos4		= float4	(pos,0.01h);

	float4 	p_current	= mul	(m_current,	pos4);
	float4 	p_previous 	= mul	(m_previous,	pos4);
	float2 	p_velocity 	= m_blur * ( (p_previous.xy/p_previous.w)-(p_current.xy/p_current.w) );
	float2  p_velocity_distance = 1-smoothstep(0,150,pos.z);
	p_velocity	= clamp(p_velocity,-MBLUR_CLAMP,+MBLUR_CLAMP);
	p_velocity *= pow(p_velocity_distance,2);
	#ifdef MBLUR_WPN
    if (pos.z < 1.4) // disable for hud
       p_velocity = 0.0;
   #endif
	
	
	
	float3 	blurred = 	c_original;

	for (int i = 1; i < MBLUR_SAMPLES; i++)
	{
		blurred += s_image.Sample( smp_rtlinear, p_velocity * half(i) + UV).rgb;
	}
	return blurred /MBLUR_SAMPLES;

}
#endif
#endif