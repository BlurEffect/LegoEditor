/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Helpers.h
*  Contains static helper functions.
*/

#include <Windows.h>
#include <xnamath.h>
#include "LegoBrickData.h"
#include "Settings.h"

//--------------------------------------------------------------------------------------
// Computes the intersection of a ray derived from the passed in cursor position with the passed in plane and 
// stores the result in the intersection parameter.
// The code is mostly based on: http://www.mvps.org/directx/articles/rayproj.htm
//--------------------------------------------------------------------------------------
static void GetIntersection( const POINT& cursorPosition, const XMFLOAT4* const pPlane, float gridLevel, int windowWidth, int windowHeight, const XMFLOAT4X4* const pViewMatrix, XMFLOAT3* pIntersection )
{
	// normalize screen coordinates
	float normX = ( cursorPosition.x/( windowWidth * 0.5f ) - 1.0f ) * ( static_cast<float>( windowWidth )/windowHeight );
	float normY = 1.0f - cursorPosition.y/ (windowHeight * 0.5f );

	// scale coordinates to frustum
	float scalX = tanf(FIELD_OF_VIEW * 0.5f) * normX;
	float scalY = tanf(FIELD_OF_VIEW * 0.5f) * normY;

	// calculate end points of the ray (using near and far clipping plane)
	XMVECTOR startPoint = XMVectorSet( scalX * NEAR_CLIPPING_PLANE, scalY * NEAR_CLIPPING_PLANE, NEAR_CLIPPING_PLANE, 0 );
	XMVECTOR endPoint = XMVectorSet( scalX * FAR_CLIPPING_PLANE, scalY * FAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE, 0 );

	// transform endpoints to world space

	XMMATRIX matWorldView = XMMatrixTranslation( 0.0f, gridLevel, 0.0f ) * XMLoadFloat4x4( pViewMatrix );
	XMVECTOR determinant;
	XMMATRIX matWorldViewInverse = XMMatrixInverse( &determinant, matWorldView );

	startPoint = XMVector3TransformCoord( startPoint, matWorldViewInverse );
	endPoint = XMVector3TransformCoord( endPoint, matWorldViewInverse );

	// Determine the point where the line intersects the grid plane
	XMStoreFloat3( pIntersection, XMPlaneIntersectLine( XMLoadFloat4( pPlane ), startPoint, endPoint ) );
}

//--------------------------------------------------------------------------------------
// Find a brick based on its id.
//--------------------------------------------------------------------------------------
class FindBrickById
{
public:
	FindBrickById( unsigned int id ) : m_id( id ){}
	bool operator()( LegoBrick brick )
	{
		return brick.m_id == m_id;
	}
private:
	unsigned int m_id;
};

//--------------------------------------------------------------------------------------
// Find a stud based on its position.
//--------------------------------------------------------------------------------------
class FindStudByPosition
{
public:
	FindStudByPosition( const IntVector3& position ) : m_position( position ){}
	bool operator()( LegoStud stud )
	{
		return stud.m_position == m_position;
	}
private:
	IntVector3 m_position;
};

//--------------------------------------------------------------------------------------
// Find a XMFLOAT3 given another XMFLOAT3
//--------------------------------------------------------------------------------------
class FindFloat3ByValue
{
public:
	FindFloat3ByValue( const XMFLOAT3& value ) : m_value( value ){}
	bool operator()( XMFLOAT3 otherValue )
	{
		return otherValue.x == m_value.x &&
			   otherValue.y == m_value.y &&
			   otherValue.z == m_value.z;
	}
private:
	XMFLOAT3 m_value;
};


