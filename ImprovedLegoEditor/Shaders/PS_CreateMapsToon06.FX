/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PS_CreateMapsToon06.fx
*  Determines the colour value for the pixel using a texture holding different
*  shades and writes the resulting colour value to a colour map. Writes normal
*  and depth information for the pixel to another render target texture.
*/

// This texture is used to determine the tone in which to shade the pixel.
// It contains a number of greyscales.
Texture2D	 ToneTexture;
SamplerState ToneSamplerState;

// Updated once per scene
cbuffer cbPerScene
{
	float4 DiffuseLightColour;  // The colour of the directional light in the scene
    float3 LightDirection;		// The direction of the directional light in the scene
	float  padding;			
};

struct PS_INPUT
{
	float4 Position	 : SV_POSITION;	
	float4 Colour	 : COLOUR;
	float3 Normal	 : NORMAL;
	//float2 TexCoord  : TEXCOORD;
	float  Depth     : DEPTH;		// Z-Position in view/camera space
};

// This shader uses two render targets
struct PS_OUTPUT
{
    float4 Colour     : SV_Target0; // The colour map to hold the original shaded image
    float4 NormalDepth: SV_Target1; // The texture to hold the normal/depth information
};

PS_OUTPUT PS(PS_INPUT input) 
{
	PS_OUTPUT output;

	// Calculate the value for the colour map

	float4 finalColour;
    float  lightIntensity;
	
	input.Normal = normalize( input.Normal );

    // Calculate the amount of light on this pixel. (Saturate clamps the value to be between 0 and 1)
    lightIntensity = saturate( dot( input.Normal, normalize( -LightDirection ) ) );
	// Query the provided texture for the shade to apply
	float4 shade = ToneTexture.Sample( ToneSamplerState, float2( lightIntensity, 0 ) );
    // Determine the final amount of diffuse color based on the diffuse color combined with the light intensity.
    finalColour = saturate( DiffuseLightColour * shade );
    // Multiply the texture pixel and the final diffuse color to get the final pixel color result.
    output.Colour = finalColour * input.Colour;

	// Calculate the value for the normal/depth map

	// Determine the normal values that will be written to the rgb channels of the texture
	
	// Make sure normal values are in the range of 0..1
	input.Normal = mul( input.Normal + 1, 0.5f ); 

	// Write the depth to the alpha channel of the texture
	output.NormalDepth = float4( input.Normal.xyz, input.Depth );

    return output;
}
