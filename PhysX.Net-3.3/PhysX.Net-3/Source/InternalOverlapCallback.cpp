#include "StdAfx.h"
#include "InternalOverlapCallback.h"
#include "OverlapHit.h"

InternalOverlapCallback::InternalOverlapCallback(PxOverlapHit *aTouches, PxU32 aMaxNbTouches)
	: PxHitCallback<PxOverlapHit>(aTouches, aMaxNbTouches)
{

}

PxAgain InternalOverlapCallback::processTouches(const PxOverlapHit* buffer, PxU32 nbHits)
{
	auto managedHits = gcnew array<OverlapHit^>(nbHits);

	for (unsigned int i = 0; i < nbHits; i++)
	{
		auto hit = OverlapHit::ToManaged((PxOverlapHit)buffer[i]);

		managedHits[i] = hit;
	}

	bool again = _managedCallback->Invoke(managedHits);

	return again;
}