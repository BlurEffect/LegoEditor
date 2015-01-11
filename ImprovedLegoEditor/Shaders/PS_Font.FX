/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PS_Font.fx
*  Forwards the input colour as the final colour for th pixel.
*/

// The texture holding all the character for the font
Texture2D	 FontTexture;
SamplerState FontSamplerState;

// Updated once per scene
cbuffer cbPerScene
{
	float4 FontColour;
};

struct PS_INPUT
{
	float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD;
};

float4 PS( PS_INPUT input ) : SV_TARGET
{

    // Sample the font texture pixel at this location.
    float4 colour = FontTexture.Sample(FontSamplerState, input.TexCoord);
	
	// The font in the texture is white characters on a black background, so if the sampled
	// value is black, make the pixel transparent (with the characters being white, it is
	// sufficient to check a single colour component to see whether the sample belongs to
	// a character or the background of the texture)
    if( colour.r == 0.0f )
    {
        colour.a = 0.0f;
		return colour;
    }
	
    // If the sample belongs to a character, get the final colour by multiplying
	// with the font colour to be used in the scene.
    colour.a = 1.0f;
	return colour * FontColour;
}

