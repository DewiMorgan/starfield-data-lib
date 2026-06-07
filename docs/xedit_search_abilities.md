# xEdit Scripting Abilities for Searching and Navigation

xEdit provides a comprehensive API for navigating the game's data graph. The API is primarily exposed through the `IwbFile`, `IwbMainRecord`, and `IwbContainer` interfaces.

## 1. Global Search & Lookup (via Script Host)
These functions are available directly within the xEdit scripting environment:

- `FileByName(name)`: Returns an `IwbFile` object by its filename (e.g., "Starfield.esm").
- `FileByLoadOrder(index)`: Returns an `IwbFile` object by its load order index.
- `FileByLoadOrderFileID(fileID)`: Returns an `IwbFile` object by its load order file ID.
- `RecordByHexFormID(hexFormID)`: Searches all loaded files for a record with the specified hex FormID.
- `RecordFromFileByFormID(file, formID)`: Retrieves a specific record from a given file using its FormID.
- `FileCount`: Returns the number of loaded files.
- `FileByIndex(index)`: Returns the file at the specified index.

## 2. File-Level Search (`IwbFile`)
Once you have a file object, you can use these methods:

- `GetRecordByEditorID(editorID)`: Finds a main record by its EditorID.
- `GetRecordByFormID(formID, ...)`: Finds a main record by its FormID.
- `GetRecord(index)`: Gets the record at the specified index.
- `GetRecordCount()`: Returns the total number of records in the file.
- `GetGroupBySignature(signature)`: Retrieves a group record by its signature.

## 3. Record-Level Navigation (`IwbMainRecord`)
The `IwbMainRecord` interface allows for deep graph traversal:

- **Inheritance/Overrides**:
  - `GetBaseRecord()`: Returns the record this one inherits from (the master).
  - `GetBaseRecordID()`: Returns the FormID of the base record.
  - `GetOverride(index)`: Gets a record that overrides this one.
  - `GetOverrideCount()`: Number of overriding records.
  - `GetWinningOverride()`: Gets the record that currently "wins" the conflict.
  - `GetHighestOverrideOrSelf(maxLoadOrder)`: Finds the most recent override.

- **References**:
  - `GetReference(index)`: Gets a record that this record references.
  - `GetReferencesCount()`: Total number of outgoing references.
  - `GetReferencedBy(index)`: Gets a record that references this one.
  - `GetReferencedByCount()`: Total number of incoming references.

- **Children**:
  - `GetChildBySignature(signature)`: Finds a child record by its signature.
  - `GetChildByGridCell(gridCell)`: Finds a child record by its location in the game world.

## 4. Element-Level Search (`IwbContainer`)
Since files and records are containers, they share these search abilities:

- `GetElementByName(name)`: Finds a child element (field/sub-record) by its name.
- `GetElementBySignature(signature)`: Finds an element by its binary signature.
- `GetElementByPath(path)`: Finds an element using a path string.
- `GetElement(index)`: Gets an element by its index.
- `GetElementCount()`: Total number of child elements.

## 5. UI-Integrated Filtering
Scripts can manipulate the xEdit UI filters to isolate records:

- `FilterEditorID`, `FilterName`, `FilterElementValue`, `FilterBaseEditorID`, `FilterBaseName`: Variables that can be set to filter the record list.
- `ApplyFilter()`: Triggers the filter application.
- `RemoveFilter()`: Clears all active filters.
