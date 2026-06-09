# Location

Класс `Location` описывает игровую локацию. Локация имеет ID, название,
описание, состояние открытия, ASCII-отрисовку, связи с другими локациями и
сундуки.

## Поля

- `int id` - уникальный номер локации.
- `std::string name` - название локации.
- `std::string description` - текстовое описание локации.
- `bool open` - состояние локации. Если значение `true`, локация открыта.
- `std::vector<int> connections` - ID локаций, в которые можно перейти.
- `std::vector<std::string> art` - строки ASCII-отрисовки локации.
- `std::vector<int> chestIds` - ID сундуков, которые находятся в локации.

## Методы

### `Location()`

Конструктор по умолчанию.

Создаёт пустую закрытую локацию с ID `0`.

### `Location(int id, const std::string& name, const std::string& description, bool open)`

Конструктор с параметрами.

Входные данные:

- `id` - ID локации;
- `name` - название локации;
- `description` - описание локации;
- `open` - начальное состояние локации.

Создаёт локацию с указанными параметрами.

### `int getId() const`

Возвращает ID локации.

### `std::string getName() const`

Возвращает название локации.

### `std::string getDescription() const`

Возвращает описание локации.

### `bool isOpen() const`

Возвращает состояние локации: открыта она или закрыта.

### `void openLocation()`

Открывает локацию.

### `void addConnection(int locationId)`

Входные данные:

- `locationId` - ID локации, с которой есть связь.

Добавляет переход в другую локацию.

### `std::vector<int> getConnections() const`

Возвращает список ID связанных локаций.

### `void addArtLine(const std::string& line)`

Входные данные:

- `line` - строка ASCII-отрисовки.

Добавляет одну строку к ASCII-отрисовке локации.

### `std::vector<std::string> getArt() const`

Возвращает все строки ASCII-отрисовки локации.

### `void addChestId(int chestId)`

Входные данные:

- `chestId` - ID сундука.

Добавляет сундук в локацию.

### `std::vector<int> getChestIds() const`

Возвращает список ID сундуков, которые находятся в локации.
