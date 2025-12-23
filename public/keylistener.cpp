#include "keylistener.h"

std::atomic<KeyListener*> KeyListener::m_instance = nullptr;
std::mutex KeyListener::m_mutex;
HHOOK KeyListener::m_hook = nullptr;
QMap<unsigned int, QString> KeyListener::m_keyMap;
QMap<unsigned int, bool> KeyListener::m_keyStateMap;

KeyListener *KeyListener::instance()
{
    KeyListener* instance = m_instance.load();  // 加载单例实例
    if (instance == nullptr)
    {
        std::lock_guard<std::mutex> lock(m_mutex);  // 加锁
        instance = m_instance.load();   // 再次加载单例实例
        if (instance == nullptr)    // 双重检查
        {
            instance = new KeyListener();   // 创建单例实例
            m_instance.store(instance); // 存储单例实例
        }
    }
    return instance;
}

QVector<QString> KeyListener::pressedKeys() const
{
    // 获取当前按下的按键列表
    QVector<QString> pressedKeys;
    for (auto key : m_keyMap.keys())
    {
        if (m_keyStateMap[key])
        {
            // 去除Left和Right前缀
            if (m_keyMap[key].startsWith("Left"))
                pressedKeys.append(m_keyMap[key].mid(4));
            else if (m_keyMap[key].startsWith("Right"))
                pressedKeys.append(m_keyMap[key].mid(5));
            else
                pressedKeys.append(m_keyMap[key]);
        }
    }

    // 排序 Control Alt Shift Win A-Z 0-9 F1-F12 其他
    std::sort(pressedKeys.begin(), pressedKeys.end(), [](const QString& a, const QString& b) -> bool {
        auto getType = [](const QString& key) -> int {
            if (key == "Control") return 0;
            if (key == "Alt") return 1;
            if (key == "Shift") return 2;
            if (key == "Win") return 3;
            if (key.length() == 1 && key[0].isLetter()) return 4;
            if (key.length() == 1 && key[0].isDigit()) return 5;
            if (key.startsWith("F")) return 6;
            return 7;
        };
        if (getType(a) != getType(b))
            return getType(a) < getType(b);
        else if (getType(a) == 6)
            return a.toInt() < b.toInt();
        return a < b;
    });

    return pressedKeys;
}

LRESULT KeyListener::keyHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0) return CallNextHookEx(m_hook, nCode, wParam, lParam);
    unsigned int vkCode = ((KBDLLHOOKSTRUCT*)lParam)->vkCode;

    if (m_keyMap.contains(vkCode))
    {
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
        {
            m_keyStateMap[vkCode] = true;
            emit instance()->keyPressed(m_keyMap[vkCode]);
        }
        else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
        {
            m_keyStateMap[vkCode] = false;
            emit instance()->keyReleased(m_keyMap[vkCode]);
        }
    }

    return CallNextHookEx(m_hook, nCode, wParam, lParam);
}

KeyListener::KeyListener()
{
    // 初始化按键映射表
    m_keyMap =
    {
        {VK_BACK,       "Backspace"},
        {VK_TAB,        "Tab"},
        {VK_RETURN,     "Enter"},
        {VK_SHIFT,      "Shift"},
        {VK_CONTROL,    "Control"},
        {VK_MENU,       "Alt"},
        {VK_PAUSE,      "Pause"},
        {VK_CAPITAL,    "CapsLock"},
        {VK_ESCAPE,     "Escape"},
        {VK_SPACE,      "Space"},
        {VK_PRIOR,      "PageUp"},
        {VK_NEXT,       "PageDown"},
        {VK_END,        "End"},
        {VK_HOME,       "Home"},
        {VK_LEFT,       "Left"},
        {VK_UP,         "Up"},
        {VK_RIGHT,      "Right"},
        {VK_DOWN,       "Down"},
        {VK_SNAPSHOT,   "PrintScreen"},
        {VK_INSERT,     "Insert"},
        {VK_DELETE,     "Delete"},
        {'0',           "0"},
        {'1',           "1"},
        {'2',           "2"},
        {'3',           "3"},
        {'4',           "4"},
        {'5',           "5"},
        {'6',           "6"},
        {'7',           "7"},
        {'8',           "8"},
        {'9',           "9"},
        {'A',           "A"},
        {'B',           "B"},
        {'C',           "C"},
        {'D',           "D"},
        {'E',           "E"},
        {'F',           "F"},
        {'G',           "G"},
        {'H',           "H"},
        {'I',           "I"},
        {'J',           "J"},
        {'K',           "K"},
        {'L',           "L"},
        {'M',           "M"},
        {'N',           "N"},
        {'O',           "O"},
        {'P',           "P"},
        {'Q',           "Q"},
        {'R',           "R"},
        {'S',           "S"},
        {'T',           "T"},
        {'U',           "U"},
        {'V',           "V"},
        {'W',           "W"},
        {'X',           "X"},
        {'Y',           "Y"},
        {'Z',           "Z"},
        {VK_LWIN,       "LeftWin"},
        {VK_RWIN,       "RightWin"},
        {VK_NUMPAD0,    "NumPad0"},
        {VK_NUMPAD1,    "NumPad1"},
        {VK_NUMPAD2,    "NumPad2"},
        {VK_NUMPAD3,    "NumPad3"},
        {VK_NUMPAD4,    "NumPad4"},
        {VK_NUMPAD5,    "NumPad5"},
        {VK_NUMPAD6,    "NumPad6"},
        {VK_NUMPAD7,    "NumPad7"},
        {VK_NUMPAD8,    "NumPad8"},
        {VK_NUMPAD9,    "NumPad9"},
        {VK_MULTIPLY,   "*"},
        {VK_ADD,        "+"},
        {VK_SUBTRACT,   "-"},
        {VK_DECIMAL,    "."},
        {VK_DIVIDE,     "/"},
        {VK_F1,         "F1"},
        {VK_F2,         "F2"},
        {VK_F3,         "F3"},
        {VK_F4,         "F4"},
        {VK_F5,         "F5"},
        {VK_F6,         "F6"},
        {VK_F7,         "F7"},
        {VK_F8,         "F8"},
        {VK_F9,         "F9"},
        {VK_F10,        "F10"},
        {VK_F11,        "F11"},
        {VK_F12,        "F12"},
        {VK_NUMLOCK,    "NumLock"},
        {VK_SCROLL,     "ScrollLock"},
        {VK_LSHIFT,     "LeftShift"},
        {VK_RSHIFT,     "RightShift"},
        {VK_LCONTROL,   "LeftControl"},
        {VK_RCONTROL,   "RightControl"},
        {VK_LMENU,      "LeftAlt"},
        {VK_RMENU,      "RightAlt"},
        {VK_OEM_1,      ";:"},
        {VK_OEM_PLUS,   "=+"},
        {VK_OEM_COMMA,  ",<"},
        {VK_OEM_MINUS,  "-_"},
        {VK_OEM_PERIOD, ".>"},
        {VK_OEM_2,      "/?"},
        {VK_OEM_3,      "`~"},
        {VK_OEM_4,      "[{"},
        {VK_OEM_5,      "\\|"},
        {VK_OEM_6,      "]}"},
        {VK_OEM_7,      "'\""},
    };

    // 初始化按键状态表
    for (auto key : m_keyMap.keys())
    {
        m_keyStateMap[key] = false;
    }

    m_hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyHookProc, GetModuleHandle(NULL), 0); // 安装键盘钩子
}

KeyListener::~KeyListener()
{
    if (m_hook)
    {
        UnhookWindowsHookEx(m_hook); // 卸载键盘钩子
        m_hook = nullptr;
    }
}
