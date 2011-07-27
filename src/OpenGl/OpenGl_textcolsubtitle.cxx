/***********************************************************************

FONCTION :
----------
File OpenGl_textcolsubtitle :


REMARQUES:
---------- 


HISTORIQUE DES MODIFICATIONS   :
--------------------------------
30-11-98 : FMN ; Creation.

************************************************************************/

/*----------------------------------------------------------------------*/
/*
* Includes
*/


#include <OpenGl_tgl_all.hxx>

#include <stddef.h>
#include <stdio.h>

#include <OpenGl_cmn_varargs.hxx>
#include <OpenGl_telem_attri.hxx>
#include <OpenGl_tsm.hxx>
#include <OpenGl_telem.hxx>
#include <OpenGl_telem_inquire.hxx>
#include <OpenGl_Memory.hxx>

/*----------------------------------------------------------------------*/
/*
* Fonctions statiques
*/

static  TStatus  TextColourSubTitleDisplay( TSM_ELEM_DATA, Tint, cmn_key* );
static  TStatus  TextColourSubTitleAdd( TSM_ELEM_DATA, Tint, cmn_key* );
static  TStatus  TextColourSubTitleDelete( TSM_ELEM_DATA, Tint, cmn_key* );
static  TStatus  TextColourSubTitlePrint( TSM_ELEM_DATA, Tint, cmn_key* );
static  TStatus  TextColourSubTitleInquire( TSM_ELEM_DATA, Tint, cmn_key* );

/*----------------------------------------------------------------------*/

static  TStatus  (*MtdTbl[])( TSM_ELEM_DATA, Tint, cmn_key* ) =
{
  0,             /* PickTraverse */
  TextColourSubTitleDisplay,
  TextColourSubTitleAdd,
  TextColourSubTitleDelete,
  TextColourSubTitlePrint,
  TextColourSubTitleInquire
};


/*----------------------------------------------------------------------*/

MtblPtr
TelTextColourSubTitleInitClass( TelType *el )
{
  *el = TelTextColourSubTitle;
  return MtdTbl;
}

/*----------------------------------------------------------------------*/

static  TStatus
TextColourSubTitleAdd( TSM_ELEM_DATA d, Tint n, cmn_key *k )
{
  tel_colour data = new TEL_COLOUR();
  //cmn_memreserve( data, 1, 0 );
  if( !data )
    return TFailure;

  *data = *(tel_colour)(k[0]->data.pdata);

  ((tsm_elem_data)(d.pdata))->pdata = data;

  return TSuccess;
}


/*----------------------------------------------------------------------*/

static  TStatus
TextColourSubTitleDisplay( TSM_ELEM_DATA data, Tint n, cmn_key *k )
{
  tel_colour      d;
  CMN_KEY         key;

  d = (tel_colour)data.pdata;

  key.id = TelTextColourSubTitle;
  key.data.pdata = d;
  TsmSetAttri( 1, &key );

  return TSuccess;
}


/*----------------------------------------------------------------------*/

static  TStatus
TextColourSubTitleDelete( TSM_ELEM_DATA data, Tint n, cmn_key *k )
{
  //cmn_freemem( data.pdata );  
  if (data.pdata)
    free(data.pdata);
  return TSuccess;
}

/*----------------------------------------------------------------------*/

static  TStatus
TextColourSubTitlePrint( TSM_ELEM_DATA data, Tint n, cmn_key *k )
{
  tel_colour p;

  p = (tel_colour)data.pdata;

  fprintf( stdout, "TelTextColourSubTitle. R = %g, G = %g, B = %g\n",
    p->rgb[0], p->rgb[1], p->rgb[2] );
  fprintf( stdout, "\n" );

  return TSuccess;
}

/*----------------------------------------------------------------------*/

static TStatus
TextColourSubTitleInquire( TSM_ELEM_DATA data, Tint n, cmn_key *k )
{
  Tint       i;
  tel_colour col;

  col = (tel_colour)data.pdata;

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

        w->gnl_colour.rgb[0] = col->rgb[0];
        w->gnl_colour.rgb[1] = col->rgb[1];
        w->gnl_colour.rgb[2] = col->rgb[2];
        break;
      }
    }
  }

  return TSuccess;
}

/*----------------------------------------------------------------------*/
