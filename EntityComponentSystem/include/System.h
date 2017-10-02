/*
	Author : Tobias Stein
	Date   : 4th July, 2016
	File   : System.h

	System base class.

	All Rights Reserved. (c) Copyright 2016.
*/

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "API.h"

#include "ISystem.h"
#include "util/FamilyTypeID.h"


namespace ECS
{
	template<class T>
	class System : public ISystem
	{
	protected:

		DECLARE_LOGGER		

	public:

		static const SystemTypeId STATIC_SYSTEM_TYPE_ID;

	protected:

		System()
		{
			DEFINE_LOGGER(typeid(T).name())
			LogInfo("System %s created.", typeid(T).name());
		}

	public:

		virtual ~System()
		{
			LogInfo("System %s released.", typeid(T).name());
		}

		virtual inline const SystemTypeId GetStaticSystemTypeID() const
		{
			return STATIC_SYSTEM_TYPE_ID;
		}

		virtual inline const char* GetSystemTypeName() const override
		{
			static const char* SYSTEM_TYPE_NAME { typeid(T).name() };
			return SYSTEM_TYPE_NAME;
		}

		virtual void Tick(float dt)
		{}

		///-------------------------------------------------------------------------------------------------
		/// Fn:	template<class... Dependencies> void System::AddDependencies(Dependencies&&... dependencies)
		///
		/// Summary:	Adds a new dependencies for this system.
		///
		/// Author:	Tobias Stein
		///
		/// Date:	28/09/2017
		///
		/// Typeparams:
		/// Dependencies - 	Type of the dependencies.
		/// Parameters:
		/// dependencies - 	Variable arguments providing [in,out] The dependencies.
		///-------------------------------------------------------------------------------------------------

		template<class... Dependencies>
		void AddDependencies(Dependencies&&... dependencies)
		{
			ECS_Engine->GetSystemManager()->AddSystemDependency(this, std::forward<Dependencies>(dependencies)...);
		}

	}; // class System<T>

	template<class T>
	const SystemTypeId System<T>::STATIC_SYSTEM_TYPE_ID = util::Internal::FamilyTypeID<ISystem>::Increment();

} // namespace ECS

#endif // __SYSTEM_H__