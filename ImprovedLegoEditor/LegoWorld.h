/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  LegoWorld.h
*  Objects of the LegoWorld class store a representation of the lego world and 
*  expose functions to alter that world (adding, removing bricks)
*/

#ifndef LEGO_WORLD_H
#define LEGO_WORLD_H

#include <windows.h>
#include <memory>
#include <xnamath.h>
#include <string>

// forward declaration
class  LegoWorldImplementation;
struct LegoBrick;
enum LegoBrickType;
struct IntVector3;
enum LegoBrickColour;
class RenderContext;

class LegoWorld
{
public:

	LegoWorld( void );

	HRESULT Initialise();
	bool	AddLegoBrick( int type, const IntVector3& gridPosition, int rotation, LegoBrickColour colour );
	bool	AddLegoStructure( unsigned int type, const IntVector3& gridPosition, int rotation );
	bool	RemoveLegoBrick( const IntVector3& gridPosition );
	HRESULT Cleanup();

	void	Update( RenderContext* pRenderContext, const XMFLOAT4 frustumPlanes[6] );

	bool	Save( std::string filename );
	bool	Load( std::string filename );

	void	StartRecording();
	bool	StopRecording( bool doSave, std::string name);

	void	GetExtentsOfStructure( int index, IntVector3* pDestination );
	int		GetNumberOfCustomStructures( void ) const;

	const std::string& GetCustomStructureName( int type ) const;

	int		GetNumberOfBricks( void ) const;
	int		GetNumberOfStuds( void ) const;

private:
	std::tr1::shared_ptr<LegoWorldImplementation> m_pImplementation;
};

#endif