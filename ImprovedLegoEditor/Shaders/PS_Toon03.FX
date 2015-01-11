/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PS_Toon03.fx
*  Examines the edge proximity value passed on by the vertex shader and compares it
*  against a given threshold. According to the result of that comparison the pixel is
*  either coloured in the outline colour or lighted/coloured as usual using a texture
*  of shades.
*/

// This texture is used to determine the tone in which to shade the pixel
Texture2D	 ToneTexture;
SamplerState ToneSamplerState;

// Updated once per scene
cbuffer cbPerScene
{
	float4 DiffuseLightColour;  // The colour of the directional light in the scene
	float4 EdgeColour;			// Colour the edge in this colour
    float3 LightDirection;		// The direction of the directional light in the scene
	float  EdgeThreshold;		// Colour pixel as edge when the edge proximity value is below this value
};

struct PS_INPUT
{
	float4 Position	: SV_POSITION;
	float4 Colour	: COLOUR;
	float3 Normal	: NORMAL;
	//float2 TexCoord : TEXCOORD;
	float  EdgeProximity : EDGEPROX;
};

float4 PS( PS_INPUT input ) : SV_TARGET
{

	// If the pixel lies close to a silhouette edge, colour it in the outline colour
	if( input.EdgeProximity < EdgeThreshold )
	{
		return EdgeColour;
	}

	// Else, colour it as usual

	float4 finalColour;
    float  lightIntensity;

    // Calculate the amount of light on this pixel. (Saturate clamps the value to be between 0 and 1)
    lightIntensity = saturate( dot( normalize(input.Normal), normalize( -LightDirection ) ) );

	// Determine the shade of this pixel using the light intensity as texture coordinate
	float4 shade = ToneTexture.Sample( ToneSamplerState, float2( lightIntensity, 0 ) );

    // Determine the final amount of diffuse color based on the diffuse color combined with the light intensity.
    finalColour = saturate( DiffuseLightColour * shade );

    // Multiply the texture pixel and the final diffuse color to get the final pixel color result.
    return finalColour * input.Colour;
}
