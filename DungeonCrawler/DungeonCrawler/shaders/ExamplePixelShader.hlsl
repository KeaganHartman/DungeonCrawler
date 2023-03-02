struct V_IN
{
	float4 pos : SV_POSITION;
	float4 col : OCOLOR;
};

float4 main(V_IN inputPixel) : SV_TARGET
{
	return inputPixel.col;
}