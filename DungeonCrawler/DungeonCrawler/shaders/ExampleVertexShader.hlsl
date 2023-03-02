
struct V_IN
{
	float4 pos : POSITION;
	float4 col : COLOR;
};

struct V_OUT
{
	float4 pos : SV_POSITION;
	float4 col : OCOLOR;
};

cbuffer SHADER_VARS : register(b0)
{
	float4x4 worldMatrix;
	float4x4 viewMatrix;
	float4x4 projMatrix;
};


V_OUT main( V_IN input )
{
	V_OUT output = (V_OUT)0;
	output.pos = input.pos;
	output.col = input.col;

	// Do Math Here
	output.pos = mul(output.pos, worldMatrix);
	output.pos = mul(output.pos, viewMatrix);
	output.pos = mul(output.pos, projMatrix);

	return output;
}