/*
 * Copyright (C) 2010-2012 Oregon <http://www.oregoncore.com/> 
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2002 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OREGON_FACTORY_HOLDER
#define OREGON_FACTORY_HOLDER

#include "Define.h"
#include "Utilities/TypeList.h"
#include "ObjectRegistry.h"
#include "Policies/SingletonImp.h"

// FactoryHolder holds a factory object of a specific type
template<class T, class Key = std::string>
class FactoryHolder
{
    public:
        typedef ObjectRegistry<FactoryHolder<T, Key >, Key > FactoryHolderRegistry;
        typedef Oregon::Singleton<FactoryHolderRegistry > FactoryHolderRepository;

        FactoryHolder(Key k) : i_key(k) {}
        virtual ~FactoryHolder() {}
        inline Key key() const { return i_key; }

        void RegisterSelf(void) { FactoryHolderRepository::Instance().InsertItem(this, i_key); }
        void DeregisterSelf(void) { FactoryHolderRepository::Instance().RemoveItem(this, false); }

        // Abstract Factory create method
        virtual T* Create(void *data = NULL) const = 0;
    private:
        Key i_key;
};

/* Permissible is a classic way of letting the object decide
 * whether how good they handle things.  This is not retricted
 * to factory selectors.
 */
template<class T>
class Permissible
{
    public:
        virtual ~Permissible() {}
        virtual int Permit(const T *) const = 0;
};
#endif
