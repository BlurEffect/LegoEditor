#include "EditorCamera.h"
#include "EditorCameraImplementation.h"


EditorCamera::EditorCamera() : m_pImplementation( new EditorCameraImplementation() )
{
}

HRESULT EditorCamera::Initialise(const XMFLOAT3& position,const XMFLOAT3& lookAt,const XMFLOAT3& up, float fov, int windowWidth, int windowHeight, float clipNear, float clipFar )
{
	return m_pImplementation -> Initialise( position, lookAt, up, fov, windowWidth, windowHeight, clipNear, clipFar );
}
	
void EditorCamera::Update( const CameraInput& input )
{
	m_pImplementation -> Update( input );
}

HRESULT EditorCamera::Cleanup( void )
{
	return m_pImplementation -> Cleanup();
}


// data access functions

const XMFLOAT4X4* const EditorCamera::GetViewMatrix( void ) const
{
	return m_pImplementation -> GetViewMatrix();
}

const XMFLOAT4X4* const EditorCamera::GetProjectionMatrix( void ) const
{
	return m_pImplementation -> GetProjectionMatrix();
}

const XMFLOAT4X4* const EditorCamera::GetOrthoProjectionMatrix( void ) const
{
	return m_pImplementation -> GetOrthoProjectionMatrix();
}

const XMFLOAT4* const EditorCamera::GetFrustumPlanes(void) const
{
	return m_pImplementation -> GetFrustumPlanes();
}

const XMFLOAT3& EditorCamera::GetCameraPosition( void ) const
{
	return m_pImplementation -> GetCameraPosition();
}