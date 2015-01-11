/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PS_Lighted.fx
*  Provides simple diffuse lighting for a given directional light source.
*/

// Updated once per scene
cbuffer cbPerScene
{
	float4 DiffuseLightColour;	// The colour of the directional light in the scene
    float3 LightDirection;		// The direction of the directional light in the scene
	float  Padding;			
};

struct PS_INPUT
{
	float4 Position	: SV_POSITION;
	float4 Colour	: COLOUR;
	float3 Normal	: NORMAL;
	//float2 TexCoord : TEXCOORD;
};

float4 PS( PS_INPUT input ) : SV_TARGET
{
    float4 finalColour;
    float  lightIntensity;

    // Calculate the amount of light on this pixel. (Saturate clamps the value to be between 0 and 1)
    lightIntensity = saturate( dot( normalize( input.Normal ), normalize( -LightDirection ) ) );

	// Determine the final amount of diffuse color based on the diffuse color combined with the light intensity.
    finalColour = saturate( DiffuseLightColour * lightIntensity );

    // Multiply the texture pixel and the final diffuse color to get the final pixel color result.
    return finalColour * input.Colour;

}
