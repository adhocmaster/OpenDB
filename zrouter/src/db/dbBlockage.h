///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (c) 2019, Nefelus Inc
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef ADS_DB_BLOCKAGE_H
#define ADS_DB_BLOCKAGE_H

#ifndef ADS_H
#include "ads.h"
#endif

#ifndef ADS_DB_ID_H
#include "dbId.h"
#endif

#ifndef ADS_DB_OBJECT_H
#include "dbObject.h"
#endif

BEGIN_NAMESPACE_ADS

class _dbInst;
class _dbBox;
class _dbDatabase;
class dbIStream;
class dbOStream;
class dbDiff;

struct _dbBlockageFlags
{
    uint _pushed_down : 1;
    uint _spare_bits  : 31;
};

class _dbBlockage : public dbObject
{
  public:
    _dbBlockageFlags   _flags;
    dbId<_dbInst>      _inst;
    dbId<_dbBox>       _bbox;

    _dbBlockage(_dbDatabase * db );
    _dbBlockage(_dbDatabase * db, const _dbBlockage & b );
    ~_dbBlockage();

    _dbInst * getInst();
    _dbBox * getBBox() const;

    int operator==( const _dbBlockage & rhs ) const;
    int operator!=( const _dbBlockage & rhs ) const { return ! operator==(rhs); }
    int operator<( const _dbBlockage & rhs ) const;
    void differences( dbDiff & diff, const char * field, const _dbBlockage & rhs ) const;
    void out( dbDiff & diff, char side, const char * field ) const;
};

inline _dbBlockage::_dbBlockage( _dbDatabase * )
{
    _flags._pushed_down = 0;
    _flags._spare_bits = 0;
}

inline _dbBlockage::_dbBlockage( _dbDatabase *, const _dbBlockage & b )
        : _flags( b._flags),
          _inst( b._inst ),
          _bbox( b._bbox )
{
}

inline _dbBlockage::~_dbBlockage()
{
}

inline dbOStream & operator<<( dbOStream & stream, const _dbBlockage & blockage )
{
    uint * bit_field = (uint *) &blockage._flags;
    stream << *bit_field;
    stream << blockage._inst;
    stream << blockage._bbox;
    return stream;
}

inline dbIStream & operator>>( dbIStream & stream, _dbBlockage & blockage )
{
    uint * bit_field = (uint *) &blockage._flags;
    stream >> *bit_field;
    stream >> blockage._inst;
    stream >> blockage._bbox;
    return stream;
}

END_NAMESPACE_ADS

#endif
