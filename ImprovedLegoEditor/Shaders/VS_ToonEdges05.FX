/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  VS_ToonEdges05.fx
*  Moves vertices along the screen-x and -y axis by an offset determined
*  by the vertex normals and the depth. This matches the toon shader used
*  by the game engine Unity.
*/

// Updated once per scene
cbuffer cbPerScene
{
	float  OutlineWidth; // Determines how thick the outline will be
	float3 Padding; 
};

// Updated once per frame
cbuffer cbPerFrame
{
	row_major float4x4 ViewProjection; // The combined view and projection matrix
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
	float4 Position  : SV_POSITION;
	//float4 Colour	 : COLOUR;
	//float3 Normal	 : NORMAL;
	//float2 TexCoord  : TEXCOORD;
};

VS_OUTPUT VS( VS_INPUT input )
{
    VS_OUTPUT output;

	// Transfrom vertex position
    output.Position = mul( input.Position, mul( input.World, ViewProjection) );
	
	// Transform normal to world-view space (only for calculation in this shader, not passed on)
	input.Normal = mul( input.Normal, (float3x3) (mul( input.World, ViewProjection ) ) );
	input.Normal = normalize( input.Normal );

	// Forward texture coordinate unchanged (not needed at the moment)
    //output.TexCoord = input.TexCoord;

	// Forward object colour (not needed at the moment)
	//output.Colour = input.Colour;

	// Determine an offset to move the vertex using the normal (normalised and transformed to screen space)
	float2 offset = input.Normal.xy;

	// Use the screen-z value to scale the outline width with the distance to ensure a uniform outline
	output.Position.xy += offset.xy * output.Position.z * OutlineWidth;

    return output;
}

/* Unity's Toon Shader:

	v2f o;
	o.pos = mul(UNITY_MATRIX_MVP, v.vertex);

	float3 norm   = mul ((float3x3)UNITY_MATRIX_IT_MV, v.normal);
	float2 offset = TransformViewToProjection(norm.xy);

	o.pos.xy += offset * o.pos.z * _Outline;
	o.color = _OutlineColor;
	return o;
*/