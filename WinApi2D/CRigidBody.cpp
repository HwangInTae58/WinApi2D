#include "framework.h"
#include "CRigidBody.h"

CRigidBody::CRigidBody()
{
	m_pOwner = nullptr;
	m_fMass = 1.f;
	m_fFricCoeff = 200.f;
	m_fMaxSpeed = 100.f;
}

CRigidBody::~CRigidBody()
{
}

CRigidBody* CRigidBody::Clone()
{
	return nullptr;
}

void CRigidBody::update()
{
}

void CRigidBody::finalupdate()
{
	float fForce = m_fForce.Length();

	if (0.f != fForce)
	{
		m_fForce.normalize();

		float m_fAccel = fForce / m_fMass;

		
	}

	// �����¿� ���� �ݴ� ���������� ���ӵ�
	if (!m_fVelocity.IsZero())
	{
		fPoint vFricDir = m_fVelocity;
		vFricDir.normalize();

		fPoint vFriction = vFricDir * (-1) * m_fFricCoeff * fDT;

		if (m_fVelocity.Length() <= vFriction.Length())
		{
			m_fVelocity = fPoint(0.f, 0.f);
		}
		else
		{
			m_fVelocity = m_fVelocity + vFriction;
		}
	}

	// �ӵ� ���� �˻�
	if (m_fMaxSpeed < m_fVelocity.Length())
	{
		m_fVelocity.normalize();
		m_fVelocity = m_fVelocity * m_fMaxSpeed;
	}

	// ��ü�� �̵�
	Move();

	m_fForce = fPoint(0.f, 0.f);
}

void CRigidBody::Move()
{
	// �̵� �ӷ�
	float fSpeed = m_fVelocity.Length();

	if (0.f != fSpeed)
	{
		// �̵� ����
		fPoint fDir = m_fVelocity;
		fDir.normalize();

		fPoint fPos = m_pOwner->GetPos();

		fPos += m_fVelocity * fDT;

		m_pOwner->SetPos(fPos);
	}
}

void CRigidBody::AddForce(fPoint _fForce)
{
	m_fForce += _fForce;
}

void CRigidBody::SetMass(float _fMass)
{
	m_fMass = _fMass;
}

float CRigidBody::GetMass()
{
	return m_fMass;
}

void CRigidBody::SetVelocity(fPoint _fVelocity)
{
	m_fVelocity = _fVelocity;
}

void CRigidBody::AddVelocity(fPoint _fVelocity)
{
	m_fVelocity += _fVelocity;
}

void CRigidBody::SetMaxSpeed(float _fMaxSpeed)
{
	m_fMaxSpeed = _fMaxSpeed;
}

float CRigidBody::GetSpeed()
{
	return  (float)m_fVelocity.Length();
}

