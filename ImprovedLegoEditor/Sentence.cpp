/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Sentence.cpp
*  Contains the function definitions for the Sentence class. Calls to these
*  functions will be forwarded to the implementation part of the Sentence class
*  "SentenceImplementation".
*/

#include "Sentence.h"
#include "SentenceImplementation.h"

//--------------------------------------------------------------------------------------
// Constructor, dynamically create an implementation object, to which all public function
// calls to this object will be forwarded. Part of separation of interface and 
// implementations.
//--------------------------------------------------------------------------------------

Sentence::Sentence() : m_pImplementation( new SentenceImplementation() )
{
}

HRESULT Sentence::Initialise( ID3D11Device* pDevice, int maxLength )
{
	return m_pImplementation -> Initialise( pDevice, maxLength );
}

HRESULT Sentence::Cleanup( void )
{
	return m_pImplementation -> Cleanup();
}

HRESULT Sentence::Update( ID3D11DeviceContext* pDeviceContext, Font* pFont, const SentenceData& sentenceData )
{
	return m_pImplementation -> Update( pDeviceContext, pFont, sentenceData );
}

void Sentence::Render( ID3D11DeviceContext* pDeviceContext )
{
	m_pImplementation -> Render( pDeviceContext );
}
