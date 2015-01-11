/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  VS_ComposeImageToon06.fx
*  Simply forwards the passed in position and texture data to the pixel shader.
*  Does not apply any transformations.
*/

struct VS_INPUT
{
	float4 Position	: POSITION;
	float2 TexCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 Position	: SV_POSITION;
	float2 TexCoord : TEXCOORD;
};


VS_OUTPUT VS( VS_INPUT input )
{
    VS_OUTPUT output;

	// Simply forwards the input data to the next stage

    output.Position = input.Position;
    output.TexCoord = input.TexCoord;

    return output;
}
