/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  EditorCameraImplementation.h
*  Implementation part of the EditorCamera class.The public interface of this class
*  and the one of the EditorCamera class have to be kept consistent.
*/

#ifndef EDITOR_CAMERA_IMPLEMENTATION_H
#define EDITOR_CAMERA_IMPLEMENTATION_H

#include <windows.h>
#include <xnamath.h>
#include "InputDataStructures.h"
#include "Settings.h"

class EditorCameraImplementation
{
public:
	EditorCameraImplementation();

	HRESULT Initialise(const XMFLOAT3& position,const XMFLOAT3& lookAt,const XMFLOAT3& up, float fov, int windowWidth, int windowHeight, float clipNear, float clipFar );
	void	Update( const CameraInput& input );
	HRESULT Cleanup( void );

	// data access
	// todo: proper return type for getters (const ref, const pointer, double const pointer???)
	const XMFLOAT4X4* const GetViewMatrix( void ) const;
	const XMFLOAT4X4* const GetProjectionMatrix( void ) const;
	const XMFLOAT4X4* const GetOrthoProjectionMatrix( void ) const;
	const XMFLOAT4* const GetFrustumPlanes(void) const;

	const XMFLOAT3& GetCameraPosition( void ) const;
private:

	void Move( const XMFLOAT3& moveVector );
	void Rotate( const XMFLOAT3& rotationVector );
	void UpdateFrustumPlanes( void );

	XMFLOAT4X4	m_viewMatrix;		// the view matrix associated to this camera
	XMFLOAT4X4	m_projMatrix;		// the projection matrix associated to this camera
	XMFLOAT4X4  m_orthoProjMatrix;	// projection matrix used for 2D rendering

	XMFLOAT3	m_position;		// the current position of the camera
	XMFLOAT3	m_rotation;		// current rotation of the camera (x->pitch, y->yaw, z->roll)

	XMFLOAT3	m_right;		// the vector from the camera pointing to the right
	XMFLOAT3	m_lookAt;		// the vector from the camera in direction to its current target (z-axis)
	XMFLOAT3	m_up;			// the vector facing up from the camera (y-axis)

	XMFLOAT4 m_frustumPlanes[6]; // the descriptions of the six planes making up the current view frustum of the camera

};

#endif