/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PS_ComposeImageToon06.fx
*  Applies a sobel filter on the depth (and possibly normal) information of a scene contained
*  in textures provided to the shader. The shader also composes the edges with the actual 
*  shaded image provided as another texture.
*
*  HLSL sobel filter code mostly taken from:
*  http://code.google.com/p/ogre-toon-shading/source/browse/trunk/OgreApp/bin/Media/materials/programs/SobelFilter.hlsl?r=4
*/

// The texture holding the original shaded image without edges
Texture2D	 ColourMap;
SamplerState ColourMapSamplerState;

// The texture holding the normal and depth information of the scene
Texture2D	 NormalDepthTexture;
SamplerState NormalDepthSamplerState;

// Updated once per scene
cbuffer cbPerScene
{
	float   ViewportWidth;			// Height of the window the application is running in (in pixels)
	float   ViewportHeight;			// Height of the window the application is running in (in pixels)
	float   EdgeThickness;			// Determines the width of the outline around the silhouettes of objects
	float   EdgeThresholdNormals;	// Determines how many edges are being drawn/how fine grained the result will be
	float   EdgeThresholdDepth;		// Determines how many edges are being drawn/how fine grained the result will be
	float3  Padding;
};


float4 getDepthEdge( float2 textureCoord )
{

	float2 xOffset = float2( EdgeThickness / ViewportWidth, 0.0f );
	float2 yOffset = float2( 0.0f, EdgeThickness / ViewportHeight );
	float2 uv = textureCoord.xy;
	float2 pp = uv - yOffset;

	// Sample the pixel and its 8 neighbours
	
	float g00 = NormalDepthTexture.Sample( NormalDepthSamplerState, pp - xOffset ).a;  
	float g01 = NormalDepthTexture.Sample( NormalDepthSamplerState, pp ).a; 
	float g02 = NormalDepthTexture.Sample( NormalDepthSamplerState, pp + xOffset ).a; 

	pp = uv;

	float g10  = NormalDepthTexture.Sample( NormalDepthSamplerState, pp - xOffset ).a; 
	float g11  = NormalDepthTexture.Sample( NormalDepthSamplerState, pp ).a; 
	float g12  = NormalDepthTexture.Sample( NormalDepthSamplerState, pp + xOffset ).a; 

	pp = uv + yOffset;

	float g20 = NormalDepthTexture.Sample( NormalDepthSamplerState, pp - xOffset ).a; 
	float g21 = NormalDepthTexture.Sample( NormalDepthSamplerState, pp ).a; 
	float g22 = NormalDepthTexture.Sample( NormalDepthSamplerState, pp + xOffset ).a; 


	// Sobel filter kernel (determines weight of a pixel in the accumulated value)
	float K00 = -1;
	float K01 = -2;
	float K02 = -1;
	float K10 = 0;
	float K11 = 0;
	float K12 = 0;
	float K20 = 1;
	float K21 = 2;
	float K22 = 1;

	float Gx = 0;
	float Gy = 0;

	// One pass in each direction

	// Gx
	Gx += g00 * K00;
	Gx += g01 * K01;
	Gx += g02 * K02;
	Gx += g10 * K10;
	Gx += g11 * K11;
	Gx += g12 * K12;
	Gx += g20 * K20;
	Gx += g21 * K21;
	Gx += g22 * K22;

	// Gy
	Gy += g00 * K00;
	Gy += g01 * K10;
	Gy += g02 * K20;
	Gy += g10 * K01;
	Gy += g11 * K11;
	Gy += g12 * K21;
	Gy += g20 * K02;
	Gy += g21 * K12;
	Gy += g22 * K22;

	float norm = sqrt( Gx * Gx + Gy * Gy );

	if( norm  > EdgeThresholdDepth )
	{
		return float4( 0.0f, 0.0f, 0.0f, 1.0f );
	}

	return float4( 1.0f, 1.0f, 1.0f, 1.0f );
}



// Currently not used
/*
// Helper function to turn a colour value into a grayscale
float getGray( float4 c )
{
	return dot( c.rgb, ( (0.33333).xxx) );
}

// Currently not used but works similar to the getDepthEdge function.
// Can be used to additionally identify crease edges.

float4 getNormalEdge( float2 textureCoord )
{
	float2 quadScreenSize = float2( ViewportWidth, ViewportHeight );

	float2 xOffset = float2( EdgeThickness / quadScreenSize.x, 0.0f );
	float2 yOffset = float2( 0.0f, EdgeThickness / quadScreenSize.y );
	float2 uv = textureCoord.xy;
	float2 pp = uv - yOffset;

	float4 cc;
	
	cc = float4( NormalDepthTexture.Sample( NormalDepthSamplerState, pp - xOffset ).xyz, 1.0f ) ;  
	float g00 = getGray( cc );

	cc = float4( NormalDepthTexture.Sample( NormalDepthSamplerState, pp ).xyz, 1.0f ); 
	float g01 = getGray( cc );

	cc = float4( NormalDepthTexture.Sample( NormalDepthSamplerState, pp + xOffset ).xyz, 1.0f ); 
	float g02 = getGray( cc );

	pp = uv;

	cc = float4( NormalDepthTexture.Sample( NormalDepthSamplerState, pp - xOffset ).xyz, 1.0f ); 
	float g10 = getGray( cc );

	cc = float4( NormalDepthTexture.Sample( NormalDepthSamplerState, pp ).xyz, 1.0f ); 
	float g11 = getGray( cc );

	cc = float4( NormalDepthTexture.Sample( NormalDepthSamplerState, pp + xOffset ).xyz, 1.0f ); 
	float g12 = getGray( cc );

	pp = uv + yOffset;

	cc = float4( NormalDepthTexture.Sample( NormalDepthSamplerState, pp - xOffset ).xyz, 1.0f ); 
	float g20 = getGray( cc );

	cc = float4( NormalDepthTexture.Sample( NormalDepthSamplerState, pp ).xyz, 1.0f ); 
	float g21 = getGray( cc );

	cc = float4( NormalDepthTexture.Sample( NormalDepthSamplerState, pp + xOffset ).xyz, 1.0f ); 
	float g22 = getGray( cc );

	// Sobel filter kernel
	float K00 = -1;
	float K01 = -2;
	float K02 = -1;
	float K10 = 0;
	float K11 = 0;
	float K12 = 0;
	float K20 = 1;
	float K21 = 2;
	float K22 = 1;

	float Gx = 0;
	float Gy = 0;

	// Gx
	Gx += g00 * K00;
	Gx += g01 * K01;
	Gx += g02 * K02;
	Gx += g10 * K10;
	Gx += g11 * K11;
	Gx += g12 * K12;
	Gx += g20 * K20;
	Gx += g21 * K21;
	Gx += g22 * K22;

	// Gy
	Gy += g00 * K00;
	Gy += g01 * K10;
	Gy += g02 * K20;
	Gy += g10 * K01;
	Gy += g11 * K11;
	Gy += g12 * K21;
	Gy += g20 * K02;
	Gy += g21 * K12;
	Gy += g22 * K22;

	float norm = sqrt( Gx * Gx + Gy * Gy );

	//float scale = NormalDepthTexture.Sample( NormalDepthSamplerState, pp ).w;

	if (norm > EdgeThresholdNormals)
	{
		return float4( 0.0f, 0.0f, 0.0f, 1.0f );
	}

	return float4( 1.0f, 1.0f, 1.0f, 1.0f );
}
*/

struct PS_INPUT
{
	float4 Position	: SV_POSITION;
	float2 TexCoord : TEXCOORD;
};


float4 PS(PS_INPUT input) : SV_TARGET
{
	// Get the colour value of the pixel
	float4 colour = float4(ColourMap.Sample( ColourMapSamplerState, input.TexCoord ).xyz, 1.0f);
	
	// Multiply the colour value with the result of the edge calculation to obtain the final colour
	// for the pixel
	return colour * getDepthEdge( input.TexCoord ) /** getNormalEdge(  input.TexCoord )*/;
}


