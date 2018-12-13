unit MetaCreate;
//Basisklasse der CustomList in Delphi geschrieben,
//um das Erzeugen von CustomListItems über ihre Metaklasse zu ermöglichen
interface
  uses
  System.Classes;
  type TOwnedCollectionClass = class of TOwnedCollection;
  type
    TBasicCustomList = class(TPersistent)

    end;
  function CreateCollection(InstanceClass: TOwnedCollectionClass; ItemClass: TCollectionItemClass; AOwner: TComponent) : TOwnedCollection;
  function CreateComponent(InstanceClass: TComponentClass; Owner: TComponent) : TComponent;

  type
    TBasicCustomListItem = class;
    TCustomListItemClass = class of TBasicCustomListItem;
    TBasicCustomListItem = class(TPersistent)
    public
      constructor Create(Owner: TBasicCustomList); virtual;
      class function NewListItem(itemClass: TCustomListItemClass; Owner: TBasicCustomList) : TBasicCustomListItem;
    end;
implementation

  function CreateCollection(InstanceClass: TOwnedCollectionClass; ItemClass: TCollectionItemClass; AOwner: TComponent) : TOwnedCollection;
    begin
        CreateCollection := InstanceClass.Create(AOwner, ItemClass);
    end;
  function CreateComponent(InstanceClass: TComponentClass; Owner: TComponent) : TComponent;
    begin
      CreateComponent := InstanceClass.Create(Owner);
    end;

  Constructor TBasicCustomListItem.Create(Owner: TBasicCustomList);
  Begin
  End;
  class function TBasicCustomListItem.NewListItem(itemClass: TCustomListItemClass; Owner: TBasicCustomList) : TBasicCustomListItem;
  begin
    result := itemClass.Create(Owner);
  end;


end.
