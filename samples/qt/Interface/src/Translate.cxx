#if !defined(CSFDB)
#error CSFDB precompiler directive is mandatory for CasCade 
#endif

#include "Translate.h"

#include "Application.h"

#include <QDir>
#include <QLayout>
#include <QComboBox>
#include <QGroupBox>
#include <QList>
#include <QListView>
#include <QFileDialog>
#include <QApplication>
#include <QWidget>
#include <QStyleFactory>

#include <AIS_Shape.hxx>
#include <AIS_InteractiveObject.hxx>

#include <FSD_File.hxx>

#include <ShapeSchema.hxx>
#include <Storage_Data.hxx>
#include <Storage_Root.hxx>
#include <Storage_HSeqOfRoot.hxx>
#include <PTopoDS_HShape.hxx>
#include <PTColStd_PersistentTransientMap.hxx>
#include <PTColStd_TransientPersistentMap.hxx>

#include <IGESControl_Reader.hxx>
#include <IGESControl_Writer.hxx>
#include <IGESControl_Controller.hxx>
#include <STEPControl_Reader.hxx>
#include <STEPControl_Writer.hxx>
#include <STEPControl_StepModelType.hxx>
#include <Interface_Static.hxx>
//#include <Interface_TraceFile.hxx>

#include <StlAPI_Writer.hxx>
#include <VrmlAPI_Writer.hxx>

#include <MgtBRep.hxx>
#include <MgtBRep_TriangleMode.hxx>

#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <BRep_Builder.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_HSequenceOfShape.hxx>

#include <Geom_Line.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Surface.hxx>


#include <Standard_ErrorHandler.hxx>
#include <Standard_CString.hxx>

// ---------------------------- TranslateDlg -----------------------------------------

class TranslateDlg : public QFileDialog
{
public:
  TranslateDlg( QWidget* = 0, Qt::WindowFlags flags = 0, bool = true );
  ~TranslateDlg();
  int                   getMode() const;
  void                  setMode( const int );
  void                  addMode( const int, const QString& );
  void                  clear();

protected:
  void                  showEvent ( QShowEvent* event );

private:
  QListView*            findListView( const QObjectList& );

private:
  QComboBox*            myBox;
  QList<int>            myList;
};

TranslateDlg::TranslateDlg( QWidget* parent, Qt::WindowFlags flags, bool modal )
: QFileDialog( parent, flags )
{
  setOption( QFileDialog::DontUseNativeDialog );
  setModal( modal );

  QGridLayout* grid = ::qobject_cast<QGridLayout*>( layout() );

  if( grid )
  {
    QVBoxLayout *vbox = new QVBoxLayout;
 
    QWidget* paramGroup = new QWidget( this );
    paramGroup->setLayout( vbox );
  
  	myBox = new QComboBox( paramGroup );
    vbox->addWidget( myBox );
	
    int row = grid->rowCount();
    grid->addWidget( paramGroup, row, 1, 1, 3 ); // make combobox occupy 1 row and 3 columns starting from 1
  }
}

TranslateDlg::~TranslateDlg()
{
}

int TranslateDlg::getMode() const
{
  if ( myBox->currentIndex() < 0 || myBox->currentIndex() > (int)myList.count() - 1 )
    return -1;
  else
    return myList.at( myBox->currentIndex() );
}

void TranslateDlg::setMode( const int mode )
{
  int idx = myList.indexOf( mode );
  if ( idx >= 0 )
    myBox->setCurrentIndex( idx );
}

void TranslateDlg::addMode( const int mode, const QString& name )
{
  myBox->show();
	myBox->addItem( name );
  myList.append( mode );
  myBox->updateGeometry();
  updateGeometry();
}

void TranslateDlg::clear()
{
    myList.clear();
    myBox->clear();
    myBox->hide();
    myBox->updateGeometry();
    updateGeometry();
}

QListView* TranslateDlg::findListView( const QObjectList & childList )
{
  QListView* listView = 0;
  for ( int i = 0, n = childList.count(); i < n && !listView; i++ )
  {
    listView = qobject_cast<QListView*>( childList.at( i ) );
    if ( !listView && childList.at( i ) )
    {
       listView = findListView( childList.at( i )->children() );
    }
  }
  return listView;
}

void TranslateDlg::showEvent ( QShowEvent* event )
{
  QFileDialog::showEvent ( event );
  QListView* aListView = findListView( children() );
  aListView->setViewMode( QListView::ListMode );
}


// ---------------------------- Translate -----------------------------------------

Translate::Translate( QObject* parent )
: QObject( parent ),
myDlg( 0 )
{
}

Translate::~Translate()
{
    if ( myDlg )
        delete myDlg;
}

QString Translate::info() const
{
    return myInfo;
}

bool Translate::importModel( const int format, const Handle(AIS_InteractiveContext)& ic )
{
    myInfo = QString();
    QString fileName = selectFileName( format, true );
    if ( fileName.isEmpty() )
        return true;

    if ( !QFileInfo( fileName ).exists() )
    {
        myInfo = QObject::tr( "INF_TRANSLATE_FILENOTFOUND" ).arg( fileName );
        return false;
    }

    QApplication::setOverrideCursor( Qt::WaitCursor );
    Handle(TopTools_HSequenceOfShape) shapes = importModel( format, fileName );
    QApplication::restoreOverrideCursor();

    return displayShSequence(ic, shapes);
}

bool Translate::displayShSequence(const Handle(AIS_InteractiveContext)& ic,
                                  const Handle(TopTools_HSequenceOfShape)& shapes )
{
  if ( shapes.IsNull() || !shapes->Length() )
        return false;

  for ( int i = 1; i <= shapes->Length(); i++ )
    ic->Display( new AIS_Shape( shapes->Value( i ) ), false );
  ic->UpdateCurrentViewer();
  return true;
}

Handle(TopTools_HSequenceOfShape) Translate::importModel( const int format, const QString& file )
{
    Handle(TopTools_HSequenceOfShape) shapes;
    try {
        switch ( format )
        {
        case FormatBREP:
            shapes = importBREP( file );
            break;
        case FormatIGES:
            shapes = importIGES( file );
            break;
        case FormatSTEP:
            shapes = importSTEP( file );
            break;
        case FormatCSFDB:
            shapes = importCSFDB( file );
            break;
        }
    } catch ( Standard_Failure ) {
        shapes.Nullify();
    }
    return shapes;
}

bool Translate::exportModel( const int format, const Handle(AIS_InteractiveContext)& ic )
{
    myInfo = QString();
    QString fileName = selectFileName( format, false );
    if ( fileName.isEmpty() )
        return true;

    Handle(TopTools_HSequenceOfShape) shapes = getShapes( ic );
    if ( shapes.IsNull() || !shapes->Length() )
        return false;

    QApplication::setOverrideCursor( Qt::WaitCursor );
    bool stat = exportModel( format, fileName, shapes );
    QApplication::restoreOverrideCursor();

    return stat;
}

bool Translate::exportModel( const int format, const QString& file, const Handle(TopTools_HSequenceOfShape)& shapes )
{
    bool status;
    try {
        switch ( format )
        {
        case FormatBREP:
            status = exportBREP( file, shapes );
            break;
        case FormatIGES:
            status = exportIGES( file, shapes );
            break;
        case FormatSTEP:
            status = exportSTEP( file, shapes );
            break;
        case FormatCSFDB:
            status = exportCSFDB( file, shapes );
            break;
        case FormatSTL:
            status = exportSTL( file, shapes );
            break;
        case FormatVRML:
            status = exportVRML( file, shapes );
            break;
        }
    } catch ( Standard_Failure ) {
        status = false;
    }
    return status;
}

Handle(TopTools_HSequenceOfShape) Translate::getShapes( const Handle(AIS_InteractiveContext)& ic )
{
    Handle(TopTools_HSequenceOfShape) aSequence;
    Handle(AIS_InteractiveObject) picked;
    for ( ic->InitCurrent(); ic->MoreCurrent(); ic->NextCurrent() )
    {
        Handle(AIS_InteractiveObject) obj = ic->Current();
        if ( obj->IsKind( STANDARD_TYPE( AIS_Shape ) ) )
        {
            TopoDS_Shape shape = Handle(AIS_Shape)::DownCast(obj)->Shape();
            if ( aSequence.IsNull() )
                aSequence = new TopTools_HSequenceOfShape();
            aSequence->Append( shape );
        }
    }
    return aSequence;
}

/*!
    Selects a file from standard dialog acoording to selection 'filter'
*/
QString Translate::selectFileName( const int format, const bool import )
{
  TranslateDlg* theDlg = getDialog( format, import );

  int ret = theDlg->exec();
    
  qApp->processEvents();

  QString file;
	QStringList fileNames;
  if ( ret != QDialog::Accepted )
      return file;

  fileNames = theDlg->selectedFiles();
	if (!fileNames.isEmpty())
    file = fileNames[0];

  if ( !QFileInfo( file ).completeSuffix().length() )
  {
    QString selFilter = theDlg->selectedNameFilter();
		int idx = selFilter.indexOf( "(*." );
    if ( idx != -1 )
    {
      QString tail = selFilter.mid( idx + 3 );
			int idx = tail.indexOf( " " );
      if ( idx == -1 )
        idx = tail.indexOf( ")" );
      QString ext = tail.left( idx );
      if ( ext.length() )
        file += QString( "." ) + ext;
    }
  }

  return file;
}

TranslateDlg* Translate::getDialog( const int format, const bool import )
{
  if ( !myDlg )
    myDlg = new TranslateDlg( 0, 0, true );

  if ( format < 0 )
    return myDlg;

  QString formatFilter = QObject::tr( QString( "INF_FILTER_FORMAT_%1" ).arg( format ).toLatin1().constData() );
  QString allFilter = QObject::tr( "INF_FILTER_FORMAT_ALL" );

  QString filter;
  filter.append( formatFilter );
	filter.append( "\t" );

	if ( import ) 
  {
    filter.append( allFilter );
		filter.append( "\t" );
	}

  cout << filter.toLatin1().constData() << endl;
  QStringList filters = filter.split( "\t" );
  myDlg->setNameFilters ( filters );

	if ( import )
  {
	  myDlg->setWindowTitle( QObject::tr( "INF_APP_IMPORT" ) );
    ((QFileDialog*)myDlg)->setFileMode( QFileDialog::ExistingFile );
  }
	else
  {
	  myDlg->setWindowTitle( QObject::tr( "INF_APP_EXPORT" ) );
    ((QFileDialog*)myDlg)->setFileMode( QFileDialog::AnyFile );
  }

  QString datadir = (QString (qgetenv ("CASROOT").constData()) + QObject::tr( QString("INF_PATH_%1").arg( format ).toLatin1().constData() ) );

  myDlg->clear();

  if ( !import )
  {
    switch ( format )
    {
      case FormatSTEP:
        myDlg->addMode( STEPControl_ManifoldSolidBrep,      QObject::tr( "INF_BREP_MOIFOLD" ) );
	      myDlg->addMode( STEPControl_FacetedBrep,            QObject::tr( "INF_BREP_FACETED" ) );
	      myDlg->addMode( STEPControl_ShellBasedSurfaceModel, QObject::tr( "INF_BREP_SHELL" ) );
	      myDlg->addMode( STEPControl_GeometricCurveSet,      QObject::tr( "INF_BREP_CURVE" ) );
        break;
      case FormatCSFDB:
        myDlg->addMode( MgtBRep_WithTriangle,    QObject::tr( "INF_TRIANGLES_YES" ) );
	      myDlg->addMode( MgtBRep_WithoutTriangle, QObject::tr( "INF_TRIANGLES_NO" ) );
        break;
     }
  }

  return myDlg;
}

// ----------------------------- Import functionality -----------------------------

Handle(TopTools_HSequenceOfShape) Translate::importBREP( const QString& file )
{
	Handle(TopTools_HSequenceOfShape) aSequence;
    TopoDS_Shape aShape;
	BRep_Builder aBuilder;
  TCollection_AsciiString  aFilePath = file.toUtf8().data();
	Standard_Boolean result = BRepTools::Read( aShape, aFilePath.ToCString(), aBuilder );
	if ( result )
    {
	    aSequence = new TopTools_HSequenceOfShape();
		aSequence->Append( aShape );
    }
    return aSequence;
}

Handle(TopTools_HSequenceOfShape) Translate::importIGES( const QString& file )
{
    Handle(TopTools_HSequenceOfShape) aSequence;
    TCollection_AsciiString  aFilePath = file.toUtf8().data();
      
    IGESControl_Reader Reader;
    int status = Reader.ReadFile(aFilePath.ToCString() );

    if ( status == IFSelect_RetDone )
    {
        aSequence = new TopTools_HSequenceOfShape();
        Reader.TransferRoots();
        TopoDS_Shape aShape = Reader.OneShape();
        aSequence->Append( aShape );
    }
	return aSequence;
}

Handle(TopTools_HSequenceOfShape) Translate::importSTEP( const QString& file )
{
	Handle(TopTools_HSequenceOfShape) aSequence;
  TCollection_AsciiString  aFilePath = file.toUtf8().data();
	STEPControl_Reader aReader;
	IFSelect_ReturnStatus status = aReader.ReadFile( aFilePath.ToCString() );
	if ( status == IFSelect_RetDone )
    {
	    //Interface_TraceFile::SetDefault();
	    bool failsonly = false;
	    aReader.PrintCheckLoad( failsonly, IFSelect_ItemsByEntity );

	    int nbr = aReader.NbRootsForTransfer();
	    aReader.PrintCheckTransfer( failsonly, IFSelect_ItemsByEntity );
	    for ( Standard_Integer n = 1; n <= nbr; n++ )
	    {
	        bool ok = aReader.TransferRoot( n );
	        int nbs = aReader.NbShapes();
	        if ( ok == true && nbs > 0 )
            {
	            aSequence = new TopTools_HSequenceOfShape();
	            for ( int i = 1; i <= nbs; i++ )
                {
		            TopoDS_Shape shape = aReader.Shape( i );
		            aSequence->Append( shape );
	            }
            }
        }
    }
	return aSequence;
}

Handle(TopTools_HSequenceOfShape) Translate::importCSFDB( const QString& file )
{
	Handle(TopTools_HSequenceOfShape) aSequence;

    // Check file type
    if ( FSD_File::IsGoodFileType( (Standard_CString)file.toLatin1().constData() ) != Storage_VSOk )
	    return aSequence;

    FSD_File fileDriver;
    TCollection_AsciiString aName( (Standard_CString)file.toLatin1().constData() );
    if ( fileDriver.Open( aName, Storage_VSRead ) != Storage_VSOk )
        return aSequence;

    Handle(ShapeSchema) schema = new ShapeSchema();
    Handle(Storage_Data) data  = schema->Read( fileDriver );
    if ( data->ErrorStatus() != Storage_VSOk )
        return aSequence;

    fileDriver.Close();

    aSequence = new TopTools_HSequenceOfShape();
    Handle(Storage_HSeqOfRoot) roots = data->Roots();
    for ( int i = 1; i <= roots->Length() ; i++ )
    {
        Handle(Storage_Root) r = roots->Value( i );
        Handle(Standard_Persistent) p = r->Object();
        Handle(PTopoDS_HShape) aPShape = Handle(PTopoDS_HShape)::DownCast(p);
        if ( !aPShape.IsNull() )
        {
	        PTColStd_PersistentTransientMap aMap;
	        TopoDS_Shape aTShape;
            MgtBRep::Translate( aPShape, aMap, aTShape, MgtBRep_WithTriangle );
            aSequence->Append( aTShape );
        }
    }

    return aSequence;
}

// ----------------------------- Export functionality -----------------------------

bool Translate::exportBREP( const QString& file, const Handle(TopTools_HSequenceOfShape)& shapes )
{
    if ( shapes.IsNull() || shapes->IsEmpty() )
        return false;

    TopoDS_Shape shape = shapes->Value( 1 );
    return BRepTools::Write( shape, (Standard_CString)file.toLatin1().constData() ); 
}

bool Translate::exportIGES( const QString& file, const Handle(TopTools_HSequenceOfShape)& shapes )
{
    if ( shapes.IsNull() || shapes->IsEmpty() )
        return false;

    IGESControl_Controller::Init();
	IGESControl_Writer writer( Interface_Static::CVal( "XSTEP.iges.unit" ),
                               Interface_Static::IVal( "XSTEP.iges.writebrep.mode" ) );
 
	for ( int i = 1; i <= shapes->Length(); i++ )
		writer.AddShape ( shapes->Value( i ) );
	writer.ComputeModel();
	return writer.Write( (Standard_CString)file.toLatin1().constData() );
}

bool Translate::exportSTEP( const QString& file, const Handle(TopTools_HSequenceOfShape)& shapes )
{
    if ( shapes.IsNull() || shapes->IsEmpty() )
        return false;

    TranslateDlg* theDlg = getDialog( -1, false );
    STEPControl_StepModelType type = (STEPControl_StepModelType)theDlg->getMode();
    if ( type < 0 )
        return false;
    
    IFSelect_ReturnStatus status;

    if ( type == STEPControl_FacetedBrep && !checkFacetedBrep( shapes ) )
    {
        myInfo = QObject::tr( "INF_FACET_ERROR" );
        return false;
    }

    STEPControl_Writer writer;
	for ( int i = 1; i <= shapes->Length(); i++ )
    {
		status = writer.Transfer( shapes->Value( i ), type );
        if ( status != IFSelect_RetDone )
            return false;
    }

    status = writer.Write( (Standard_CString)file.toLatin1().constData() );

    switch ( status )
    {
    case IFSelect_RetError:
        myInfo = QObject::tr( "INF_DATA_ERROR" );
        break;
    case IFSelect_RetFail:
        myInfo = QObject::tr( "INF_WRITING_ERROR" );
        break;
    case IFSelect_RetVoid:
        myInfo = QObject::tr( "INF_NOTHING_ERROR" );
        break;
    }
    return status == IFSelect_RetDone;
}

bool Translate::exportCSFDB( const QString& file, const Handle(TopTools_HSequenceOfShape)& shapes )
{
    if ( shapes.IsNull() || shapes->IsEmpty() )
        return false;

    TranslateDlg* theDlg = getDialog( -1, false );
    MgtBRep_TriangleMode type = (MgtBRep_TriangleMode)theDlg->getMode();
    if ( type < 0 )
        return false;

    FSD_File fileDriver;

    Handle(ShapeSchema) schema = new ShapeSchema();
    Handle(Storage_Data) data  = new Storage_Data();
    data->ClearErrorStatus();

    data->SetApplicationName( TCollection_ExtendedString( "Sample Import / Export" ) );
    data->SetApplicationVersion( "1" );
    data->SetDataType( TCollection_ExtendedString( "Shapes" ) );
    data->AddToUserInfo( "Storing a persistent set of shapes in a flat file" );
    data->AddToComments( TCollection_ExtendedString( "Application is based on CasCade 5.0 Professional" ) );

    if ( fileDriver.Open( (Standard_CString)file.toLatin1().constData(), Storage_VSWrite ) != Storage_VSOk )
    {
        myInfo = QObject::tr( "INF_TRANSLATE_ERROR_CANTSAVEFILE" ).arg( file );
        return false;
    }

    PTColStd_TransientPersistentMap aMap;
	for ( int i = 1; i <= shapes->Length(); i++ )
	{
		TopoDS_Shape shape = shapes->Value( i );
		if ( shape.IsNull() )
		{
			myInfo = QObject::tr( "INF_TRANSLATE_ERROR_INVALIDSHAPE" );
			return false;
        }

        Handle(PTopoDS_HShape) pshape = MgtBRep::Translate( shape, aMap, type );
		TCollection_AsciiString objName = TCollection_AsciiString( "Object_" ) + TCollection_AsciiString( i );
		data->AddRoot( objName, pshape );
	}

    schema->Write( fileDriver, data );
    fileDriver.Close();

    if ( data->ErrorStatus() != Storage_VSOk )
    {
        myInfo = QObject::tr( "INF_TRANSLATE_ERROR_CANTSAVEDATA" );
        return false;
    } 
    return true;
}

bool Translate::exportSTL( const QString& file, const Handle(TopTools_HSequenceOfShape)& shapes )
{
    if ( shapes.IsNull() || shapes->IsEmpty() )
        return false;

	TopoDS_Compound res;
	BRep_Builder builder;
	builder.MakeCompound( res );

	for ( int i = 1; i <= shapes->Length(); i++ )
	{
		TopoDS_Shape shape = shapes->Value( i );
		if ( shape.IsNull() ) 
		{
			myInfo = QObject::tr( "INF_TRANSLATE_ERROR_INVALIDSHAPE" );
			return false;
        }
		builder.Add( res, shape );
	}

	StlAPI_Writer writer;
	writer.Write( res, (Standard_CString)file.toLatin1().constData() );

    return true;
}

bool Translate::exportVRML( const QString& file, const Handle(TopTools_HSequenceOfShape)& shapes )
{
    if ( shapes.IsNull() || shapes->IsEmpty() )
        return false;

	TopoDS_Compound res;
	BRep_Builder builder;
	builder.MakeCompound( res );

	for ( int i = 1; i <= shapes->Length(); i++ )
	{
		TopoDS_Shape shape = shapes->Value( i );
		if ( shape.IsNull() )
		{
			myInfo = QObject::tr( "INF_TRANSLATE_ERROR_INVALIDSHAPE" );
			return false;
        }
		builder.Add( res, shape );
	}

	VrmlAPI_Writer writer;
	writer.Write( res, (Standard_CString)file.toLatin1().constData() );

    return true;
}

bool Translate::checkFacetedBrep( const Handle(TopTools_HSequenceOfShape)& shapes )
{
	bool err = false;
	for ( int i = 1; i <= shapes->Length(); i++ )
	{
	    TopoDS_Shape shape = shapes->Value( i );
        for ( TopExp_Explorer fexp( shape, TopAbs_FACE ); fexp.More() && !err; fexp.Next() )
		{
		    Handle(Geom_Surface) surface = BRep_Tool::Surface( TopoDS::Face( fexp.Current() ) );
		    if ( !surface->IsKind( STANDARD_TYPE( Geom_Plane ) ) )
		        err = true;
		}
        for ( TopExp_Explorer eexp( shape, TopAbs_EDGE ); eexp.More() && !err; eexp.Next() )
		{
		    Standard_Real fd, ld;
		    Handle(Geom_Curve) curve = BRep_Tool::Curve( TopoDS::Edge( eexp.Current() ), fd, ld );
		    if ( !curve->IsKind( STANDARD_TYPE( Geom_Line ) ) )
		        err = true;
		}
	}
	return !err;
}



