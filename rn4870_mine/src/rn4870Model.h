#ifndef RN2483_MODEL_H
#define RN2483_MODEL_H

typedef enum {
    noAnswer,
    partialAnswer,
    completeAnswer,
    dataAnswer
}AnswerE;

typedef enum {
    enterDatamode,
    dataMode,
    enterConfmode,
    confMode
}RN4870StatusE;

#define DELAY_INTERNAL_CMD      10
#define INTERNAL_CMD_TIMEOUT    100 // 1000 mSec = 1Sec.
#define SMALL_ANSWER_DATA_LEN   20

#define PROMPT                  "CMD>"
#define PROMPT_FIRST_CHAR       'C'
#define PROMPT_LAST_CHAR        '>'
#define PROMPT_LEN              4
#define PROMPT_END              "END"
#define PROMPT_END_FIST_CHAR    'E'
#define PROMPT_END_LAST_CHAR    'D'
#define PROMPT_MIDDLE_AOK		'O'

#define DATA_LAST_CHAR          '\r'

#define CONF_CHAR               '$'

// commands
#define FACTORY_RESET           "SF,1"
#define EXIT_CONF               "---\r"
#define RESTART_CONF			"r,1"

#define AUTO_RANDOM_ADDRESS     "&R"
#define USER_RANDOM_ADDRESS     "&,"

#define SET_NAME                "S-,"
#define GET_NAME                "&R"

#define SET_BAUDRATE            "SB,"
#define GET_BAUDRATE            "GB"

#define SET_POWERSAVE           "SO,"
#define GET_POWERSAVE           "GO"
#define POWERSAVE_ENABLE        '1'
#define POWERSAVE_DISABLE       '0'

#define GET_FWVERSION           "GDF"
#define GET_HWVERSION           "GDH"
#define GET_SWVERSION           "GDR"
#define GET_SERIALNUM           "GDS"

#define CLEAR_ALL_SERV			"PZ"
#define CREATE_SERV				"PS,"
#define CREATE_CHAR				"PC,"
#define WRITE_CHAR				"SHW,"

#endif
