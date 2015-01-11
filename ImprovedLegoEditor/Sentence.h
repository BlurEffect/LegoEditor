/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Sentence.h
*  Encapsulates a piece of text.
*/

#ifndef SENTENCE_H
#define SENTENCE_H

#include <windows.h>
#include <memory>
#include <D3D11.h>
#include <xnamath.h>

// forward declaration
class SentenceImplementation;
struct SentenceData;
class Font;

class Sentence
{
public:
	Sentence( void );

	HRESULT Initialise( ID3D11Device* pDevice, int maxLength );
	HRESULT Cleanup( void );
	HRESULT	Update( ID3D11DeviceContext* pDeviceContext, Font* pFont, const SentenceData& sentenceData );
	void	Render( ID3D11DeviceContext* pDeviceContext );
private:
	std::tr1::shared_ptr<SentenceImplementation> m_pImplementation;
};


#endif