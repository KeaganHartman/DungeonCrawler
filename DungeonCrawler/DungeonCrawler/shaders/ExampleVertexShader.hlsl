
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


V_OUT main( V_IN input )
{
	V_OUT output = (V_OUT)0;
	output.pos = input.pos;
	output.col = input.col;

	return output;
}