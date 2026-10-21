#ifndef MOTOR_STATUS_H
#define MOTOR_STATUS_H

/*
 * motor_status.h
 *
 * Interpretazione dei valori di status motore MDrive.
 *
 * Comandi supportati (tutti numerici, non byte di bit):
 *
 * 1) PR ER  (Error Code)
 *    Risposta: codice numerico intero
 *    0  = No Error
 *    83 = Reached plus  LIMIT switch
 *    84 = Reached minus LIMIT switch
 *    86 = Stall detected
 *    (vedi Appendix B del manuale MDrive per lista completa)
 *
 * 2) PR DE  (Drive Enable)
 *    Risposta: 0 = Drive disabled (motore spento)
 *              1 = Drive enabled  (motore acceso)
 *
 * 3) PR MV  (Moving Flag)
 *    Risposta: 0 = Fermo
 *              1 = In moto
 */

/* ════════════════════════════════════════════════
 *  Codici errore MDrive rilevanti
 * ════════════════════════════════════════════════ */
#define MDRIVE_ERR_NONE         0
#define MDRIVE_ERR_LIMIT_PLUS   83
#define MDRIVE_ERR_LIMIT_MINUS  84
#define MDRIVE_ERR_STALL        86

/* ════════════════════════════════════════════════
 *  Struttura MDriveStatus  (PR ER + PR DE + PR MV)
 *
 *  Tutti i campi hanno semantica positiva (1 = condizione vera).
 * ════════════════════════════════════════════════ */
typedef struct {
    int error_code;    /* valore grezzo di PR ER                     */
    int drive_enable;  /* PR DE: 1 = drive ON,  0 = drive OFF        */
    int in_motion;     /* PR MV: 1 = in moto,   0 = fermo            */
    int limit_right;   /* 1 se error_code == 83 (plus  limit)        */
    int limit_left;    /* 1 se error_code == 84 (minus limit)        */
    int stall;         /* 1 se error_code == 86                      */
} MDriveStatus;

/* Alias per compatibilità con il codice esistente */
typedef MDriveStatus MotorStatus;

/* ════════════════════════════════════════════════
 *  Struttura TotalStatus  (stato globale asse singolo)
 *
 *  Per MDrive ogni IOC gestisce un solo asse.
 *  Manteniamo la struttura per coerenza con il resto del codice.
 * ════════════════════════════════════════════════ */
typedef struct {
    int drive_enable;  /* 1 = drive ON,  0 = drive OFF               */
    int in_motion;     /* 1 = in moto,   0 = fermo                   */
    int limit_right;   /* 1 = plus  limit scattato                   */
    int limit_left;    /* 1 = minus limit scattato                   */
    int stall;         /* 1 = stall rilevato                         */
} TotalStatus;

/* ════════════════════════════════════════════════
 *  API MDriveStatus
 * ════════════════════════════════════════════════ */

/*
 * parse_mdrive_status()
 * Popola la struttura MDriveStatus dai tre valori letti dal device.
 *   error_code : valore di PR ER
 *   drive_en   : valore di PR DE
 *   moving     : valore di PR MV
 * Ritorna 0 OK, -1 se ms e' NULL.
 */
int parse_mdrive_status(int error_code, int drive_en, int moving, MDriveStatus *ms);

/*
 * mdrive_status_ok()
 * Ritorna 1 se il motore e' in stato operativo normale:
 *   drive enabled AND nessun errore.
 */
int mdrive_status_ok(MDriveStatus *ms);

/*
 * mdrive_is_ready()
 * Ritorna 1 se il motore e' pronto a muoversi:
 *   drive enabled AND fermo AND nessun errore.
 */
int mdrive_is_ready(MDriveStatus *ms);

/*
 * print_mdrive_status()
 * Stampa lo stato completo su stdout (debug IOC).
 *   label : nome asse (es. "X", "Y", "Motor1")
 *   ms    : puntatore alla struttura MDriveStatus
 */
void print_mdrive_status(const char *label, MDriveStatus *ms);

/* ════════════════════════════════════════════════
 *  API TotalStatus
 * ════════════════════════════════════════════════ */

/*
 * parse_total_status()
 * Popola la struttura TotalStatus da MDriveStatus.
 * Ritorna 0 OK, -1 se ts e' NULL.
 */
int parse_total_status(MDriveStatus *ms, TotalStatus *ts);

/*
 * print_total_status()
 * Stampa lo stato globale su stdout (debug IOC).
 *   ms : puntatore alla struttura MDriveStatus
 */
void print_total_status(MDriveStatus *ms);

#endif /* MOTOR_STATUS_H */

