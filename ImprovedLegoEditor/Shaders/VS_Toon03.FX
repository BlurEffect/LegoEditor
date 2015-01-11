/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  VS_Toon03.fx
*  Uses the dot product between the normal of a vertex and the eye vector to determine
*  whether a vertex lies close to a silhouette edge and passes that value on to the
*  pixel shader, together with the transformed position, normal and the vertex colour.
*/

// Updated once per frame
cbuffer cbPerFrame
{
	row_major float4x4 ViewProjection;  // The combined view and projection matrix
	float3			   ViewPosition;	// The world position of the camera
	float			   Padding;
};

struct VS_INPUT
{
	// vertex data
	float4 Position	 : POSITION;
	float3 Normal	 : NORMAL;
	float3 AvgNormal : AVGNORMAL;
	float2 TexCoord  : TEXCOORD;

	// instance data
	row_major float4x4 World  : WORLD;   // row_major "automatically" transposes matrix
	float4			   Colour : COLOUR;
};

struct VS_OUTPUT
{
	float4 Position	: SV_POSITION;
	float4 Colour	: COLOUR;
	float3 Normal	: NORMAL;
	//float2 TexCoord : TEXCOORD;
	float  EdgeProximity : EDGEPROX; // result of dot product between view vector and vertex normal (if close to zero -> close to edge)
};

VS_OUTPUT VS( VS_INPUT input )
{
    VS_OUTPUT output;

	// Transform the vertex position to world space
	input.Position = mul( float4( input.Position.xyz, 1.0f ), input.World );

	// Calculate the vector between the vertex and the view position
	float3 eyeVector = normalize( ViewPosition - input.Position.xyz );

	// Transform the vertex position
    output.Position = mul( input.Position, ViewProjection );
	
	// Transform normal to world space 
	output.Normal = mul( input.Normal, (float3x3) input.World );

	// calculate the dot product between the vertex normal and the view vector 
	// (determines whether vertex lies close to the edge or not)
	output.EdgeProximity = saturate( dot( normalize( output.Normal ), eyeVector ) );

	// forward texture coordinate unchanged (not needed at the moment)
    // output.TexCoord = input.TexCoord;

	// forward object colour
	output.Colour = input.Colour;

    return output;
}