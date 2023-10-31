#include <ctype.h>
#include <internal/attribute.h>

#ifndef __OPTIMIZE_SIZE__

// clang-format off
__weak const unsigned char __ctype_table[256] = {
  ['\0']   = __CTYPE_CTRL_CHAR,
  ['\x01'] = __CTYPE_CTRL_CHAR, // SOH
  ['\x02'] = __CTYPE_CTRL_CHAR, // STX
  ['\x03'] = __CTYPE_CTRL_CHAR, // ETX
  ['\x04'] = __CTYPE_CTRL_CHAR, // EOT
  ['\x05'] = __CTYPE_CTRL_CHAR, // ENG
  ['\x06'] = __CTYPE_CTRL_CHAR, // ACK
  ['\a']   = __CTYPE_CTRL_CHAR,
  ['\b']   = __CTYPE_CTRL_CHAR,
  ['\t']   = __CTYPE_SPACE_CHAR | __CTYPE_CTRL_CHAR | __CTYPE_BLANK_CHAR,
  ['\n']   = __CTYPE_SPACE_CHAR | __CTYPE_CTRL_CHAR,
  ['\v']   = __CTYPE_SPACE_CHAR | __CTYPE_CTRL_CHAR,
  ['\f']   = __CTYPE_SPACE_CHAR | __CTYPE_CTRL_CHAR,
  ['\r']   = __CTYPE_SPACE_CHAR | __CTYPE_CTRL_CHAR,
  ['\x0e'] = __CTYPE_CTRL_CHAR, // SO
  ['\x0f'] = __CTYPE_CTRL_CHAR, // SI
  ['\x10'] = __CTYPE_CTRL_CHAR, // DLE
  ['\x11'] = __CTYPE_CTRL_CHAR, // DC1
  ['\x12'] = __CTYPE_CTRL_CHAR, // DC2
  ['\x13'] = __CTYPE_CTRL_CHAR, // DC3
  ['\x14'] = __CTYPE_CTRL_CHAR, // DC4
  ['\x15'] = __CTYPE_CTRL_CHAR, // NAK
  ['\x16'] = __CTYPE_CTRL_CHAR, // SYN
  ['\x17'] = __CTYPE_CTRL_CHAR, // ETB
  ['\x18'] = __CTYPE_CTRL_CHAR, // CAN
  ['\x19'] = __CTYPE_CTRL_CHAR, // EM
  ['\x1a'] = __CTYPE_CTRL_CHAR, // SUB
  ['\x1b'] = __CTYPE_CTRL_CHAR, // ECS
  ['\x1c'] = __CTYPE_CTRL_CHAR, // FS
  ['\x1d'] = __CTYPE_CTRL_CHAR, // GS
  ['\x1e'] = __CTYPE_CTRL_CHAR, // RS
  ['\x1f'] = __CTYPE_CTRL_CHAR, // US
  [' ']    = __CTYPE_SPACE_CHAR | __CTYPE_BLANK_CHAR,
  ['!']    = __CTYPE_PUNCT_CHAR,
  ['"']    = __CTYPE_PUNCT_CHAR,
  ['#']    = __CTYPE_PUNCT_CHAR,
  ['$']    = __CTYPE_PUNCT_CHAR,
  ['%']    = __CTYPE_PUNCT_CHAR,
  ['&']    = __CTYPE_PUNCT_CHAR,
  ['\'']   = __CTYPE_PUNCT_CHAR,
  ['(']    = __CTYPE_PUNCT_CHAR,
  [')']    = __CTYPE_PUNCT_CHAR,
  ['*']    = __CTYPE_PUNCT_CHAR,
  ['+']    = __CTYPE_PUNCT_CHAR,
  [',']    = __CTYPE_PUNCT_CHAR,
  ['-']    = __CTYPE_PUNCT_CHAR,
  ['.']    = __CTYPE_PUNCT_CHAR,
  ['/']    = __CTYPE_PUNCT_CHAR,
  ['0']    = __CTYPE_NUMBER_CHAR,
  ['1']    = __CTYPE_NUMBER_CHAR,
  ['2']    = __CTYPE_NUMBER_CHAR,
  ['3']    = __CTYPE_NUMBER_CHAR,
  ['4']    = __CTYPE_NUMBER_CHAR,
  ['5']    = __CTYPE_NUMBER_CHAR,
  ['6']    = __CTYPE_NUMBER_CHAR,
  ['7']    = __CTYPE_NUMBER_CHAR,
  ['8']    = __CTYPE_NUMBER_CHAR,
  ['9']    = __CTYPE_NUMBER_CHAR,
  [':']    = __CTYPE_PUNCT_CHAR,
  [';']    = __CTYPE_PUNCT_CHAR,
  ['<']    = __CTYPE_PUNCT_CHAR,
  ['=']    = __CTYPE_PUNCT_CHAR,
  ['>']    = __CTYPE_PUNCT_CHAR,
  ['?']    = __CTYPE_PUNCT_CHAR,
  ['@']    = __CTYPE_PUNCT_CHAR,
  ['A']    = __CTYPE_UPPER_CHAR | __CTYPE_HEX_CHAR,
  ['B']    = __CTYPE_UPPER_CHAR | __CTYPE_HEX_CHAR,
  ['C']    = __CTYPE_UPPER_CHAR | __CTYPE_HEX_CHAR,
  ['D']    = __CTYPE_UPPER_CHAR | __CTYPE_HEX_CHAR,
  ['E']    = __CTYPE_UPPER_CHAR | __CTYPE_HEX_CHAR,
  ['F']    = __CTYPE_UPPER_CHAR | __CTYPE_HEX_CHAR,
  ['G']    = __CTYPE_UPPER_CHAR,
  ['H']    = __CTYPE_UPPER_CHAR,
  ['I']    = __CTYPE_UPPER_CHAR,
  ['J']    = __CTYPE_UPPER_CHAR,
  ['K']    = __CTYPE_UPPER_CHAR,
  ['L']    = __CTYPE_UPPER_CHAR,
  ['M']    = __CTYPE_UPPER_CHAR,
  ['N']    = __CTYPE_UPPER_CHAR,
  ['O']    = __CTYPE_UPPER_CHAR,
  ['P']    = __CTYPE_UPPER_CHAR,
  ['Q']    = __CTYPE_UPPER_CHAR,
  ['R']    = __CTYPE_UPPER_CHAR,
  ['S']    = __CTYPE_UPPER_CHAR,
  ['T']    = __CTYPE_UPPER_CHAR,
  ['U']    = __CTYPE_UPPER_CHAR,
  ['V']    = __CTYPE_UPPER_CHAR,
  ['W']    = __CTYPE_UPPER_CHAR,
  ['X']    = __CTYPE_UPPER_CHAR,
  ['Y']    = __CTYPE_UPPER_CHAR,
  ['Z']    = __CTYPE_UPPER_CHAR,
  ['[']    = __CTYPE_PUNCT_CHAR,
  ['\\']   = __CTYPE_PUNCT_CHAR,
  [']']    = __CTYPE_PUNCT_CHAR,
  ['^']    = __CTYPE_PUNCT_CHAR,
  ['_']    = __CTYPE_PUNCT_CHAR,
  ['`']    = __CTYPE_PUNCT_CHAR,
  ['a']    = __CTYPE_LOWER_CHAR | __CTYPE_HEX_CHAR,
  ['b']    = __CTYPE_LOWER_CHAR | __CTYPE_HEX_CHAR,
  ['c']    = __CTYPE_LOWER_CHAR | __CTYPE_HEX_CHAR,
  ['d']    = __CTYPE_LOWER_CHAR | __CTYPE_HEX_CHAR,
  ['e']    = __CTYPE_LOWER_CHAR | __CTYPE_HEX_CHAR,
  ['f']    = __CTYPE_LOWER_CHAR | __CTYPE_HEX_CHAR,
  ['g']    = __CTYPE_LOWER_CHAR,
  ['h']    = __CTYPE_LOWER_CHAR,
  ['i']    = __CTYPE_LOWER_CHAR,
  ['j']    = __CTYPE_LOWER_CHAR,
  ['k']    = __CTYPE_LOWER_CHAR,
  ['l']    = __CTYPE_LOWER_CHAR,
  ['m']    = __CTYPE_LOWER_CHAR,
  ['n']    = __CTYPE_LOWER_CHAR,
  ['o']    = __CTYPE_LOWER_CHAR,
  ['p']    = __CTYPE_LOWER_CHAR,
  ['q']    = __CTYPE_LOWER_CHAR,
  ['r']    = __CTYPE_LOWER_CHAR,
  ['s']    = __CTYPE_LOWER_CHAR,
  ['t']    = __CTYPE_LOWER_CHAR,
  ['u']    = __CTYPE_LOWER_CHAR,
  ['v']    = __CTYPE_LOWER_CHAR,
  ['w']    = __CTYPE_LOWER_CHAR,
  ['x']    = __CTYPE_LOWER_CHAR,
  ['y']    = __CTYPE_LOWER_CHAR,
  ['z']    = __CTYPE_LOWER_CHAR,
  ['{']    = __CTYPE_PUNCT_CHAR,
  ['|']    = __CTYPE_PUNCT_CHAR,
  ['}']    = __CTYPE_PUNCT_CHAR,
  ['~']    = __CTYPE_PUNCT_CHAR,
  ['\x7f'] = __CTYPE_CTRL_CHAR, // DEL
  [0x80]   = 0,
  [0x81]   = 0,
  [0x82]   = 0,
  [0x83]   = 0,
  [0x84]   = 0,
  [0x85]   = 0,
  [0x86]   = 0,
  [0x87]   = 0,
  [0x88]   = 0,
  [0x89]   = 0,
  [0x8a]   = 0,
  [0x8b]   = 0,
  [0x8c]   = 0,
  [0x8d]   = 0,
  [0x8e]   = 0,
  [0x8f]   = 0,
  [0x90]   = 0,
  [0x91]   = 0,
  [0x92]   = 0,
  [0x93]   = 0,
  [0x94]   = 0,
  [0x95]   = 0,
  [0x96]   = 0,
  [0x97]   = 0,
  [0x98]   = 0,
  [0x99]   = 0,
  [0x9a]   = 0,
  [0x9b]   = 0,
  [0x9c]   = 0,
  [0x9d]   = 0,
  [0x9e]   = 0,
  [0x9f]   = 0,
  [0xa0]   = 0,
  [0xa1]   = 0,
  [0xa2]   = 0,
  [0xa3]   = 0,
  [0xa4]   = 0,
  [0xa5]   = 0,
  [0xa6]   = 0,
  [0xa7]   = 0,
  [0xa8]   = 0,
  [0xa9]   = 0,
  [0xaa]   = 0,
  [0xab]   = 0,
  [0xac]   = 0,
  [0xad]   = 0,
  [0xae]   = 0,
  [0xaf]   = 0,
  [0xb0]   = 0,
  [0xb1]   = 0,
  [0xb2]   = 0,
  [0xb3]   = 0,
  [0xb4]   = 0,
  [0xb5]   = 0,
  [0xb6]   = 0,
  [0xb7]   = 0,
  [0xb8]   = 0,
  [0xb9]   = 0,
  [0xba]   = 0,
  [0xbb]   = 0,
  [0xbc]   = 0,
  [0xbd]   = 0,
  [0xbe]   = 0,
  [0xbf]   = 0,
  [0xc0]   = 0,
  [0xc1]   = 0,
  [0xc2]   = 0,
  [0xc3]   = 0,
  [0xc4]   = 0,
  [0xc5]   = 0,
  [0xc6]   = 0,
  [0xc7]   = 0,
  [0xc8]   = 0,
  [0xc9]   = 0,
  [0xca]   = 0,
  [0xcb]   = 0,
  [0xcc]   = 0,
  [0xcd]   = 0,
  [0xce]   = 0,
  [0xcf]   = 0,
  [0xd0]   = 0,
  [0xd1]   = 0,
  [0xd2]   = 0,
  [0xd3]   = 0,
  [0xd4]   = 0,
  [0xd5]   = 0,
  [0xd6]   = 0,
  [0xd7]   = 0,
  [0xd8]   = 0,
  [0xd9]   = 0,
  [0xda]   = 0,
  [0xdb]   = 0,
  [0xdc]   = 0,
  [0xdd]   = 0,
  [0xde]   = 0,
  [0xdf]   = 0,
  [0xe0]   = 0,
  [0xe1]   = 0,
  [0xe2]   = 0,
  [0xe3]   = 0,
  [0xe4]   = 0,
  [0xe5]   = 0,
  [0xe6]   = 0,
  [0xe7]   = 0,
  [0xe8]   = 0,
  [0xe9]   = 0,
  [0xea]   = 0,
  [0xeb]   = 0,
  [0xec]   = 0,
  [0xed]   = 0,
  [0xee]   = 0,
  [0xef]   = 0,
  [0xf0]   = 0,
  [0xf1]   = 0,
  [0xf2]   = 0,
  [0xf3]   = 0,
  [0xf4]   = 0,
  [0xf5]   = 0,
  [0xf6]   = 0,
  [0xf7]   = 0,
  [0xf8]   = 0,
  [0xf9]   = 0,
  [0xfa]   = 0,
  [0xfb]   = 0,
  [0xfc]   = 0,
  [0xfd]   = 0,
  [0xfe]   = 0,
  [0xff]   = 0,
};
// clang-format on

#endif // __OPTIMIZE_SIZE__
