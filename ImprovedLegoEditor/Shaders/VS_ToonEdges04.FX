/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  VS_ToonEdges04.fx
*  Moves vertices along the screen-z axis by a certain bias in order to create an
*  outline around an object as these backfaces now appear slightly in front of the
*  neighbouring front faces. The transformed position is then forwarded to the 
*  pixel shader.
*/

// Updated once per scene
cbuffer cbPerScene
{
	float  MoveBias;  // The vertices are moved by this distance in screen-z
	float3 Padding;
};

// Updated once per frame
cbuffer cbPerFrame
{
	row_major float4x4 ViewProjection; // The combined view and projection matrix
	float3			   EyePosition;	   // The position of the camera in view space
	float			   Padding2;
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
	float4	           Colour : COLOUR;
};

struct VS_OUTPUT
{
	float4 Position	: SV_POSITION;
	//float4 Colour	: COLOUR;
	//float3 Normal	: NORMAL;
	//float2 TexCoord : TEXCOORD;
};

VS_OUTPUT VS( VS_INPUT input )
{
    VS_OUTPUT output;

	// Transform the vertex position to world space
	output.Position = mul( input.Position, input.World );

	// Calculate the distance between the vertex and the camera
	float distanceFromCamera = abs( distance( float4( EyePosition, 1.0f ), output.Position ) );

	// Transform the vertex position
	output.Position = mul( output.Position, ViewProjection );

	// Move the vertex along the screen-z axis.
	// Use distance from camera to scale outline.
	output.Position.z -= MoveBias /** ( 1/distanceFromCamera )*/; 

	// Transform normal to world space (not needed at the moment)
	// output.Normal = mul( input.Normal, input.World );

	// forward texture coordinate unchanged (not needed at the moment)
    // output.TexCoord = input.TexCoord;

	// forward object colour (not needed at the moment)
	// output.Colour = input.Colour;

    return output;
}
