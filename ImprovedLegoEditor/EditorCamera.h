/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  EditorCamera.h
*  The EditorCamera class contains the camera used to navigate
*  within the lego editor.
*/

#ifndef EDITOR_CAMERA_H
#define EDITOR_CAMERA_H

#include <windows.h>
#include <memory>
#include <xnamath.h>

// forward declaration
class EditorCameraImplementation;
struct CameraInput;

class EditorCamera
{
public:
	EditorCamera();

	HRESULT Initialise(const XMFLOAT3& position,const XMFLOAT3& lookAt,const XMFLOAT3& up, float fov, int windowWidth, int windowHeight, float clipNear, float clipFar );
	void	Update( const CameraInput& input );
	HRESULT Cleanup( void );

	const XMFLOAT4X4* const GetViewMatrix( void ) const;
	const XMFLOAT4X4* const GetProjectionMatrix( void ) const;
	const XMFLOAT4X4* const GetOrthoProjectionMatrix( void ) const;
	const XMFLOAT4* const GetFrustumPlanes(void) const;

	const XMFLOAT3& GetCameraPosition( void ) const;
private:
	std::tr1::shared_ptr<EditorCameraImplementation> m_pImplementation;	
};

#endif