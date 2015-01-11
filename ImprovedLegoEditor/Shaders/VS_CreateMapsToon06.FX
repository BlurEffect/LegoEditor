/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  VS_CreateMapsToon06.fx
*  Performs the standard transformations on vertex positions and normals
*  and forwards the rest of the vertex input to the pixel shader. Additionally
*  to that, the shader passes normals and position data in view space to the next 
*  stage.
*/

// Updated once per frame
cbuffer cbPerFrame
{
	row_major float4x4 ViewProjection;		// Combined view and projection matrices
	row_major float4x4 ViewMatrix;			// The current view matrix
};

struct VS_INPUT
{
	// vertex data
	float4 Position	 : POSITION;
	float3 Normal	 : NORMAL;
	float3 AvgNormal : AVGNORMAL;
	float2 TexCoord  : TEXCOORD;

	// instance data
	row_major float4x4 World  : WORLD;   
	float4	 Colour : COLOUR;
};

struct VS_OUTPUT
{
	float4 Position  : SV_POSITION;
	float4 Colour	 : COLOUR;
	float3 Normal	 : NORMAL;
	//float2 TexCoord  : TEXCOORD;
	float  Depth     : DEPTH;
};

VS_OUTPUT VS( VS_INPUT input )
{
    VS_OUTPUT output;

	// for the colour map

	// transform the position to world space
	input.Position = mul( float4( input.Position.xyz, 1.0f) , input.World );
	// transfrom vertex position
    output.Position  = mul( input.Position, ViewProjection );
	// transform normal to world space and normalize the normal vector
	output.Normal = mul( float4( input.Normal, 0.0f), input.World ).xyz;
	
	// forward texture coordinate unchanged (not needed at the moment)
    // output.TexCoord = input.TexCoord;
	
	// forward vertex colour
	output.Colour = input.Colour;

	// for the normal/depth map

	// Calculate the z-position of the vertex in camera space
	output.Depth = mul( input.Position, ViewMatrix ).z;
	// Make sure the depth value is set between 0 and 1 by dividing the value by the far clipping distance
	output.Depth = mul(( output.Depth ), 0.00025f );

    return output;
}
