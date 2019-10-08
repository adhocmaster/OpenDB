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

#ifndef ADS_DB_VIA_GENERATE_RULE_H
#define ADS_DB_VIA_GENERATE_RULE_H

#ifndef ADS_H
#include "ads.h"
#endif

#ifndef ADS_GEOM_H
#include "geom.h"
#endif

#ifndef ADS_DB_TYPES_H
#include "dbTypes.h"
#endif

#ifndef ADS_DB_ID_H
#include "dbId.h"
#endif

#ifndef ADS_DB_OBJECT_H
#include "dbObject.h"
#endif

#ifndef ADS_DB_VECTOR_H
#include "dbVector.h"
#endif

BEGIN_NAMESPACE_ADS

class _dbTechLayer;
class _dbBox;
class _dbDatabase;
class dbIStream;
class dbOStream;
class dbDiff;

//
// These flags keep track of the variations between difference LEF versions
//
struct _dbTechViaGenerateRuleFlags
{
    uint   _default                : 1; 
    uint   _spare_bits             : 31;
};
    
class _dbTechViaGenerateRule : public dbObject
{
  public:
    // PERSISTANT-MEMBERS
    _dbTechViaGenerateRuleFlags _flags; 
    char *                      _name;
    dbVector<uint>              _layer_rules;

    _dbTechViaGenerateRule( _dbDatabase *, const _dbTechViaGenerateRule & v );
    _dbTechViaGenerateRule( _dbDatabase * );
    ~_dbTechViaGenerateRule();

    int operator==( const _dbTechViaGenerateRule & rhs ) const;
    int operator!=( const _dbTechViaGenerateRule & rhs ) const { return ! operator==(rhs); }
    int operator<( const _dbTechViaGenerateRule & rhs ) const
    {
        return strcmp( _name, rhs._name ) < 0;
    }
    
    void differences( dbDiff & diff, const char * field, const _dbTechViaGenerateRule & rhs ) const;
    void out( dbDiff & diff, char side, const char * field ) const;
};

dbOStream & operator<<( dbOStream & stream, const _dbTechViaGenerateRule & v );
dbIStream & operator>>( dbIStream & stream, _dbTechViaGenerateRule & v );

END_NAMESPACE_ADS

#endif
