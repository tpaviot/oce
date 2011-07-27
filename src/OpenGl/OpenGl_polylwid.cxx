
#include <OpenGl_tgl_all.hxx>

#include <stddef.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <OpenGl_cmn_varargs.hxx>
#include <OpenGl_telem_attri.hxx>
#include <OpenGl_tsm.hxx>
#include <OpenGl_telem.hxx>
#include <OpenGl_telem_inquire.hxx>
#include <OpenGl_Memory.hxx>

static  TStatus  PolylineWidthDisplay( TSM_ELEM_DATA, Tint, cmn_key* );
static  TStatus  PolylineWidthAdd( TSM_ELEM_DATA, Tint, cmn_key* );
static  TStatus  PolylineWidthDelete( TSM_ELEM_DATA, Tint, cmn_key* );
static  TStatus  PolylineWidthPrint( TSM_ELEM_DATA, Tint, cmn_key* );
static  TStatus  PolylineWidthInquire( TSM_ELEM_DATA, Tint, cmn_key* );

static  TStatus  (*MtdTbl[])( TSM_ELEM_DATA, Tint, cmn_key* ) =
{
  0,             /* PickTraverse */
  PolylineWidthDisplay,
  PolylineWidthAdd,
  PolylineWidthDelete,
  PolylineWidthPrint,
  PolylineWidthInquire
};


MtblPtr
TelPolylineWidthInitClass( TelType *el )
{
  *el = TelPolylineWidth;
  return MtdTbl;
}

static  TStatus
PolylineWidthAdd( TSM_ELEM_DATA d, Tint n, cmn_key *k )
{
  Tfloat *data = new Tfloat();

  if( !data )
    return TFailure;

  *data = k[0]->data.fdata;

  ((tsm_elem_data)(d.pdata))->pdata = data;

  return TSuccess;
}


static  TStatus
PolylineWidthDisplay( TSM_ELEM_DATA data, Tint n, cmn_key *k )
{
  CMN_KEY     key;

  key.id = TelPolylineWidth;
  key.data.fdata = *(Tfloat*)(data.pdata);
  TsmSetAttri( 1, &key );

  return TSuccess;
}


static  TStatus
PolylineWidthDelete( TSM_ELEM_DATA data, Tint n, cmn_key *k )
{
  if (data.pdata)
    free(data.pdata);
  return TSuccess;
}


static  TStatus
PolylineWidthPrint( TSM_ELEM_DATA data, Tint n, cmn_key *k )
{
  fprintf( stdout, "TelPolylineWidth. Value = %g\n", *(Tfloat *)(data.pdata));
  fprintf( stdout, "\n" );

  return TSuccess;
}


static TStatus
PolylineWidthInquire( TSM_ELEM_DATA data, Tint n, cmn_key *k )
{
  Tint    i;
  Tfloat *f = (Tfloat *)data.pdata;

  for( i = 0; i < n; i++ )
  {
    switch( k[i]->id )
    {
    case INQ_GET_SIZE_ID:
      {
        k[i]->data.ldata = sizeof( Tint );
        break;
      }
    case INQ_GET_CONTENT_ID:
      {
        TEL_INQ_CONTENT *c;
        Teldata         *w;

        c = (tel_inq_content)k[i]->data.pdata;
        w = c->data;
        c->act_size = 0;
        w->fdata = *f;
        break;
      }
    }
  }

  return TSuccess;
}
