#ifdef D3D9
	#define SV_TARGET COLOR0
	#define ARG_VPOS ,float2 coord : VPOS
	#define FRAG_COORD coord.xy
#else
	#define FRAG_COORD In.v_position.xy
	#define ARG_VPOS
#endif

struct VS_INPUT {
#ifdef D3D9
	float4 a_position : POSITION;
	float4 a_texcoord : TEXCOORD0;
	float4 a_color    : COLOR0;
#else
	int4 a_position   : POSITION;
	uint4 a_texcoord  : TEXCOORD0;
	float4 a_color    : COLOR0;
#endif
};

struct VS_OUTPUT {
#ifdef D3D9
	float4 v_position  : POSITION;
#else
	float4 v_position  : SV_POSITION;
#endif
	float4 v_texcoord  : TEXCOORD0;
	float4 v_color     : TEXCOORD1;
};

#ifdef VERTEX
#ifdef D3D12
	cbuffer ConstantBuffer : register(b0)
	{
		float4x4 Projection;
	};
#else
	float4x4 Projection : register(c0);
#endif

	VS_OUTPUT main(VS_INPUT In) {
		VS_OUTPUT Out;
		float2 page;
		page.x = frac (In.a_position.z / 16.0) * 1024.0;
		page.y = floor(In.a_position.z / 16.0) * 256.0;
		Out.v_texcoord     = In.a_texcoord;
		Out.v_texcoord.xy += page;
		Out.v_texcoord.xy *= float2(1.0 / 1024.0, 1.0 / 512.0);
		Out.v_color        = In.a_color;
		Out.v_color.xyz   *= In.a_texcoord.z;
		Out.v_position     = mul(Projection, float4(In.a_position.xy, 0.0, 1.0));
		return Out;
	}
#else
#ifdef D3D9
	SamplerState s_texture : register(s0);
	SamplerState s_lut : register(s1);
#else
	SamplerState samplerState : register(s0);
	SamplerState samplerStateLUT : register(s1);
	Texture2D s_texture : register(t0);
	Texture2D s_lut : register(t1);
#endif

	float4 main(VS_OUTPUT In ARG_VPOS) : SV_TARGET {
#ifdef D3D9
		float2 color_rg = tex2D(s_texture, In.v_texcoord.xy).ra;
#else
		float2 color_rg = s_texture.Sample(samplerState, In.v_texcoord.xy).rg;
#endif
		if(color_rg.x == 0.0 && color_rg.y == 0.0)
		{
			discard;
		}
		
#ifdef D3D9
		float4 color = tex2D(s_lut, color_rg);
#else
		float4 color = s_lut.Sample(samplerStateLUT, color_rg);
#endif

		color = color * In.v_color;
		float4x4 dither = float4x4(
			-4.0,  +0.0,  -3.0,  +1.0,
			+2.0,  -2.0,  +3.0,  -1.0,
			-3.0,  +1.0,  -4.0,  +0.0,
			+3.0,  -1.0,  +2.0,  -2.0) / 255.0;
		int2 dc = int2(frac(FRAG_COORD / 4.0) * 4.0);
		color.xyz += dither[dc.x][dc.y] * In.v_texcoord.w;

		return color;
	}
#endif