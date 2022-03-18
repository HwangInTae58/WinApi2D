#pragma once
#include "CGameObject.h"

class CGameObject;
class CRigidBody :public CGameObject
{
	friend class CGameObject;
private:
	CGameObject* m_pOwner;

	fPoint	 m_fForce;
	fPoint	 m_fAccel;
	fPoint	 m_fAccelA;
	fPoint	 m_fVelocity;
	float	 m_fMass;

	float	 m_fFricCoeff;
	float	 m_fMaxSpeed;
public:
	CRigidBody();
	virtual ~CRigidBody();
	virtual CRigidBody* Clone();
	virtual void update();

	virtual void finalupdate();

	void Move();
	void AddForce(fPoint _vForce);
	void SetMass(float _fMass);
	float GetMass();
	void SetVelocity(fPoint _vVelocity);
	void AddVelocity(fPoint _vVelocity);
	void SetMaxSpeed(float _fMaxSpeed);
	float GetSpeed();
};
