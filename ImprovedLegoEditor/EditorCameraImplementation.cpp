/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  EditorCameraImplementation.cpp
*  Contains the function definitions for the EditorCameraImplementation class.
*/

#include "EditorCameraImplementation.h"

EditorCameraImplementation::EditorCameraImplementation( void ) : m_position( 0, 0, 0 ), 
																 m_rotation( 0, 0, 0 ), 
																 m_right( 0, 0, 0 ), 
																 m_lookAt( 0, 0, 0 ), 
																 m_up( 0, 0, 0 )

{
	XMStoreFloat4x4( &m_viewMatrix, XMMatrixIdentity() );
	XMStoreFloat4x4( &m_projMatrix, XMMatrixIdentity() );
}

//--------------------------------------------------------------------------------------
// Initialise the editor camera
//--------------------------------------------------------------------------------------
HRESULT EditorCameraImplementation::Initialise(const XMFLOAT3& position,const XMFLOAT3& lookAt,const XMFLOAT3& up, float fov, int windowWidth, int windowHeight, float clipNear, float clipFar )
{
	m_position	 = position;
	m_lookAt	 = lookAt;
	m_up		 = up;		
		
	XMStoreFloat3(&m_right, XMVector3Cross(XMLoadFloat3(&m_up), XMLoadFloat3(&m_lookAt)));

	XMStoreFloat4x4(&m_viewMatrix, XMMatrixLookAtLH( XMLoadFloat3( &m_position ), XMLoadFloat3( &m_lookAt ), XMLoadFloat3( &m_up ) ) );
	XMStoreFloat4x4(&m_projMatrix, XMMatrixPerspectiveFovLH( fov, static_cast<float>(windowWidth)/windowHeight, clipNear, clipFar ) );
	
	// Create an orthographic projection matrix for 2D rendering
	XMStoreFloat4x4( &m_orthoProjMatrix, XMMatrixOrthographicLH( static_cast<float>( windowWidth ), static_cast<float>( windowHeight ), static_cast<float>( clipNear ), static_cast<float>( clipFar ) ) );

	// Update the frustum planes according to the new view and projection matrix
	UpdateFrustumPlanes();

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Update the camera and compute the new view matrix according to the user input
//--------------------------------------------------------------------------------------
void EditorCameraImplementation::Update( const CameraInput& input )
{
	if( !input.m_doUpdate)
		return;

	// update the camera position and rotation
	Move( input.m_movement );
	Rotate( input.m_rotation );
	
	// build the new view matrix

	m_viewMatrix._11 = m_right.x; 
	m_viewMatrix._12 = m_up.x; 
	m_viewMatrix._13 = m_lookAt.x;
	m_viewMatrix._14 = 0.0f;

	m_viewMatrix._21 = m_right.y; 
	m_viewMatrix._22 = m_up.y; 
	m_viewMatrix._23 = m_lookAt.y;
	m_viewMatrix._24 = 0.0f;

	m_viewMatrix._31 = m_right.z; 
	m_viewMatrix._32 = m_up.z; 
	m_viewMatrix._33 = m_lookAt.z;
	m_viewMatrix._34 = 0.0f;

	XMStoreFloat( &m_viewMatrix._41, - XMVector3Dot( XMLoadFloat3( &m_position ), XMLoadFloat3( &m_right ) ) );
	XMStoreFloat( &m_viewMatrix._42, - XMVector3Dot( XMLoadFloat3( &m_position ), XMLoadFloat3( &m_up ) ) );
	XMStoreFloat( &m_viewMatrix._43, - XMVector3Dot( XMLoadFloat3( &m_position ), XMLoadFloat3( &m_lookAt ) ) );
	m_viewMatrix._44 = 1.0f;

	// Update the frustum planes according to the new view matrix
	UpdateFrustumPlanes();
}

//--------------------------------------------------------------------------------------
// Updates the camera position according to the move vector passed to the function
// taking into account the movement speed factors defined in "EditorCameraConstants.h"
//--------------------------------------------------------------------------------------
void EditorCameraImplementation::Move( const XMFLOAT3& moveVector )
{
	XMStoreFloat3( &m_position, XMLoadFloat3( &m_position ) 
								+ XMLoadFloat3( &m_right ) * moveVector.x * CAMERA_MOVEMENT_SPEED.x		// add horizontal movement
								+ XMLoadFloat3( &m_up ) * moveVector.y * CAMERA_MOVEMENT_SPEED.y			// add vertical movement
								+ XMLoadFloat3( &m_lookAt ) * moveVector.z * CAMERA_MOVEMENT_SPEED.z);		// add movement along z-axis

}

//--------------------------------------------------------------------------------------
// Updates the camera rotation according to the rotation vector passed to the function
// taking into account the rotation speed factors defined in "EditorCameraConstants.h"
//--------------------------------------------------------------------------------------
void EditorCameraImplementation::Rotate( const XMFLOAT3& rotationVector )
{
	// todo: get rid of the manual modulo-style code and use something else?
	// todo: use quaternions instead of rotation matrix?

	// update pitch
	m_rotation.x += rotationVector.x * CAMERA_ROTATION_SPEED.x;

	if(m_rotation.x > 360)
		m_rotation.x -= 360.0f;
	else if(m_rotation.x < 0)
		m_rotation.x += 360.0f;
	
	// update yaw
	m_rotation.y += rotationVector.y * CAMERA_ROTATION_SPEED.y;

	if(m_rotation.y > 360)
		m_rotation.y -= 360.0f;
	else if(m_rotation.y < 0)
		m_rotation.y += 360.0f;
	
	// update roll
	m_rotation.z += rotationVector.z * CAMERA_ROTATION_SPEED.z;

	if(m_rotation.z > 360)
		m_rotation.z -= 360.0f;
	else if(m_rotation.z < 0)
		m_rotation.z += 360.0f;
	
	// update the camera vectors

	// reset camera vectors (prevent numerical errors from accumulating)
	m_up	 = XMFLOAT3(0.0f,1.0f,0.0f);
	m_lookAt = XMFLOAT3(0.0f,0.0f,1.0f);
	m_right	 = XMFLOAT3(1.0f,0.0f,0.0f);
	
	// apply yaw
	XMMATRIX yawMatrix = XMMatrixRotationAxis( XMLoadFloat3( &m_up ), XMConvertToRadians( m_rotation.y ) ); 
	XMStoreFloat3( &m_lookAt, XMVector3TransformCoord( XMLoadFloat3( &m_lookAt ), yawMatrix ) );
	XMStoreFloat3( &m_right, XMVector3TransformCoord( XMLoadFloat3( &m_right ), yawMatrix ) );

	// apply pitch
	XMMATRIX pitchMatrix = XMMatrixRotationAxis( XMLoadFloat3( &m_right ), XMConvertToRadians( m_rotation.x ) ); 
	XMStoreFloat3( &m_lookAt, XMVector3TransformCoord( XMLoadFloat3( &m_lookAt ), pitchMatrix ) );
	XMStoreFloat3( &m_up, XMVector3TransformCoord( XMLoadFloat3( &m_up ), pitchMatrix ) );
	
	// apply roll
	XMMATRIX rollMatrix = XMMatrixRotationAxis( XMLoadFloat3( &m_lookAt ), XMConvertToRadians( m_rotation.z ) ); 
	XMStoreFloat3( &m_right, XMVector3TransformCoord( XMLoadFloat3( &m_right ), rollMatrix ) );
	XMStoreFloat3( &m_up, XMVector3TransformCoord( XMLoadFloat3( &m_up ), rollMatrix ) );
}


//--------------------------------------------------------------------------------------
// Free ressources
//--------------------------------------------------------------------------------------
HRESULT EditorCameraImplementation::Cleanup( void )
{
	return S_OK;
}

//--------------------------------------------------------------------------------------
// Update the array of planes representing the view frustum of the camera.
//--------------------------------------------------------------------------------------
void EditorCameraImplementation::UpdateFrustumPlanes( void )
{
	// Determine the view-projection matrix
	XMFLOAT4X4 viewProjection;
	XMStoreFloat4x4( &viewProjection, XMMatrixMultiply( XMLoadFloat4x4( &m_viewMatrix ), XMLoadFloat4x4( &m_projMatrix ) ) );

	// Determine the plane descriptions for all six frustum planes

    // Left plane
    m_frustumPlanes[0].x = viewProjection._14 + viewProjection._11;
    m_frustumPlanes[0].y = viewProjection._24 + viewProjection._21;
    m_frustumPlanes[0].z = viewProjection._34 + viewProjection._31;
    m_frustumPlanes[0].w = viewProjection._44 + viewProjection._41;
 
    // Right plane
    m_frustumPlanes[1].x = viewProjection._14 - viewProjection._11;
    m_frustumPlanes[1].y = viewProjection._24 - viewProjection._21;
    m_frustumPlanes[1].z = viewProjection._34 - viewProjection._31;
    m_frustumPlanes[1].w = viewProjection._44 - viewProjection._41;
 
    // Top plane
    m_frustumPlanes[2].x = viewProjection._14 - viewProjection._12;
    m_frustumPlanes[2].y = viewProjection._24 - viewProjection._22;
    m_frustumPlanes[2].z = viewProjection._34 - viewProjection._32;
    m_frustumPlanes[2].w = viewProjection._44 - viewProjection._42;
 
    // Bottom plane
    m_frustumPlanes[3].x = viewProjection._14 + viewProjection._12;
    m_frustumPlanes[3].y = viewProjection._24 + viewProjection._22;
    m_frustumPlanes[3].z = viewProjection._34 + viewProjection._32;
    m_frustumPlanes[3].w = viewProjection._44 + viewProjection._42;
 
    // Near plane
    m_frustumPlanes[4].x = viewProjection._13;
    m_frustumPlanes[4].y = viewProjection._23;
    m_frustumPlanes[4].z = viewProjection._33;
    m_frustumPlanes[4].w = viewProjection._43;
 
    // Far plane
    m_frustumPlanes[5].x = viewProjection._14 - viewProjection._13;
    m_frustumPlanes[5].y = viewProjection._24 - viewProjection._23;
    m_frustumPlanes[5].z = viewProjection._34 - viewProjection._33;
    m_frustumPlanes[5].w = viewProjection._44 - viewProjection._43;
 
    // Normalize the planes
    for ( int i = 0; i < 6; i++ )
    {
		XMStoreFloat4( &m_frustumPlanes[i], XMPlaneNormalize( XMLoadFloat4( &m_frustumPlanes[i] ) ) );
    }
}


// data access functions

const XMFLOAT4X4* const EditorCameraImplementation::GetViewMatrix( void ) const
{
	return &m_viewMatrix;
}

const XMFLOAT4X4* const EditorCameraImplementation::GetProjectionMatrix( void ) const
{
	return &m_projMatrix;
}

const XMFLOAT4X4* const EditorCameraImplementation::GetOrthoProjectionMatrix( void ) const
{
	return &m_orthoProjMatrix;
}

const XMFLOAT4* const EditorCameraImplementation::GetFrustumPlanes(void) const
{
	return m_frustumPlanes;
}

const XMFLOAT3& EditorCameraImplementation::GetCameraPosition( void ) const
{
	return m_position;
}