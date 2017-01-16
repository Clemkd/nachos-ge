/* syscalls.h
 * 	Nachos system call interface.  These are Nachos kernel operations
 * 	that can be invoked from user programs, by trapping to the kernel
 *	via the "syscall" instruction.
 *
 *	This file is included by user programs and by the Nachos kernel.
 *
 * Copyright (c) 1992-1993 The Regents of the University of California.
 * All rights reserved.  See copyright.h for copyright notice and limitation
 * of liability and disclaimer of warranty provisions.
*/
/**
 * \file syscall.h
 * \brief Nachos system call interface.  These are Nachos kernel operations
 * 	that can be invoked from user programs, by trapping to the kernel
 *	via the "syscall" instruction.
 *
 *	This file is included by user programs and by the Nachos kernel.
 */

#ifndef SYSCALLS_H
#define SYSCALLS_H
#define sem_t void
#define MAX_SEM_NAME_SIZE 30

/* system call codes -- used by the stubs to tell the kernel which system call
 * is being asked for
 */
#define SC_Halt				0
#define SC_Exit				1
#define SC_Exec				2
#define SC_Join				3
#define SC_Create			4
#define SC_Open				5
#define SC_Read				6
#define SC_Write			7
#define SC_Close			8
#define SC_Fork				9
#define SC_Yield			10
#define SC_PutChar			11
#define SC_PutString 		12
#define SC_GetChar			13
#define SC_GetString		14
#define SC_GetInt			15
#define SC_PutInt			16
#define SC_UserThreadCreate	17
#define SC_UserThreadExit	18
#define SC_UserThreadJoin	19
#define SC_UserSemCreate 20
#define SC_UserSemP 21
#define SC_UserSemV 22
#define SC_UserSemDelete 23
#define SC_ForkExec	24
#define SC_Assert 25

#ifdef IN_USER_MODE

// LB: This part is read only on compiling the test/*.c files.
// It is *not* read on compiling test/start.S


/* The system call interface.  These are the operations the Nachos
 * kernel needs to support, to be able to run user programs.
 *
 * Each of these is invoked by a user program by simply calling the
 * procedure; an assembly language stub stuffs the system call code
 * into a register, and traps to the kernel.  The kernel procedures
 * are then invoked in the Nachos kernel, after appropriate error checking,
 * from the system call entry point in exception.cc.
 */

/* Stop Nachos, and print out performance stats */

/**
 * \fn void Halt () __attribute__((noreturn))
 * \brief Permet à l'utilisateur d'arreter la machine. Attendra la fin de
 * l'execution de tous les threads avant de s'executer
 *
*/
void Halt () __attribute__((noreturn));

/**
 * \fn void Exit (int status) __attribute__((noreturn))
 * \brief Permet à l'utilisateur de terminer le thread.
 *
*/

/* Address space control operations: Exit, Exec, and Join */

/* This user program is done (status = 0 means exited normally). */
void Exit (int status) __attribute__((noreturn));

/* A unique identifier for an executing user program (address space) */
typedef int SpaceId;


/**
 * \fn SpaceId Exec (char *name);
 * \brief Run the executable, stored in the Nachos file "name", and return the
  * address space identifier
 * \param name TODO
 * \return TODO
 *
*/
/* Run the executable, stored in the Nachos file "name", and return the
 * address space identifier
 */
SpaceId Exec (char *name);

/* Only return once the the user program "id" has finished.
 * Return the exit status.
 */

 /**
  * \fn int Join (SpaceId id);
  * \brief  Only return once the the user program "id" has finished.
   * Return the exit status.
  * \param id TODO
  * \return TODO
 */
int Join (SpaceId id);


/* File system operations: Create, Open, Read, Write, Close
 * These functions are patterned after UNIX -- files represent
 * both files *and* hardware I/O devices.
 *
 * If this assignment is done before doing the file system assignment,
 * note that the Nachos file system has a stub implementation, which
 * will work for the purposes of testing out these routines.
 */

/* A unique identifier for an open Nachos file. */
typedef int OpenFileId;

/* when an address space starts up, it has two open files, representing
 * keyboard input and display output (in UNIX terms, stdin and stdout).
 * Read and Write can be used directly on these, without first opening
 * the console device.
 */

#define ConsoleInput	0
#define ConsoleOutput	1

/**
 * \fn void Create (char *name)
 * \brief Create a Nachos file, with "name"
 * \param name TODO
 * \return TODO
*/

/* Create a Nachos file, with "name" */
void Create (char *name);

/**
 * \fn OpenFileId Open (char *name)
 * \brief Open the Nachos file "name", and return an "OpenFileId" that can
  * be used to read and write to the file.
 * \param name TODO
 * \return TODO
*/

/* Open the Nachos file "name", and return an "OpenFileId" that can
 * be used to read and write to the file.
 */
OpenFileId Open (char *name);

/**
 * \fn void Write (char *buffer, int size, OpenFileId id)
 * \brief Write "size" bytes from "buffer" to the open file.
 * \param buffer TODO
 * \param size TODO
 * \param id TODO
 * \return TODO
*/
/* Write "size" bytes from "buffer" to the open file. */
void Write (char *buffer, int size, OpenFileId id);

/**
 * \fn int Read (char *buffer, int size, OpenFileId id)
 * \brief Read "size" bytes from the open file into "buffer".
  * Return the number of bytes actually read -- if the open file isn't
  * long enough, or if it is an I/O device, and there aren't enough
  * characters to read, return whatever is available (for I/O devices,
  * you should always wait until you can return at least one character).
 * \param buffer TODO
 * \param size TODO
 * \param id TODO
 * \return TODO
*/

/* Read "size" bytes from the open file into "buffer".
 * Return the number of bytes actually read -- if the open file isn't
 * long enough, or if it is an I/O device, and there aren't enough
 * characters to read, return whatever is available (for I/O devices,
 * you should always wait until you can return at least one character).
 */
int Read (char *buffer, int size, OpenFileId id);

/**
 * \fn void void Close (OpenFileId id)
 * \brief Close the file, we're done reading and writing to it.
 * \param name TODO
 * \return TODO
*/
/* Close the file, we're done reading and writing to it. */
void Close (OpenFileId id);



/* User-level thread operations: Fork and Yield.  To allow multiple
 * threads to run within a user program.
 */

 /**
  * \fn void Fork (void (*func) ())
  * \brief User-level thread operations: Fork and Yield.  To allow multiple
   * threads to run within a user program. Fork a thread to run a procedure ("func") in the *same* address space
   * as the current thread.
  * \param  TODO
 */

/* Fork a thread to run a procedure ("func") in the *same* address space
 * as the current thread.
 */
void Fork (void (*func) ());

/**
 * \fn void void Yield ()
 * \brief User-level thread operations: Fork and Yield.  To allow multiple
  * threads to run within a user program. Yield the CPU to another runnable thread, whether in this address space
   * or not.
*/

/* Yield the CPU to another runnable thread, whether in this address space
 * or not.
 */
void Yield ();

/**
 * \fn void PutChar(char c)
 * \brief Ecrit un caractère sur la console standard.
 * La fonction grantit un affichage synchorne d'un caractère.
 * \param c Le paramètre doit être de type char.
 */
void PutChar(char c);

/**
 * \fn char GetChar()
 * \brief Obtient un caractère depuis l'entrée de la console standard et le retourne.
 *
 * \return Retourne le caractère entré dans la console
 */
char GetChar();

/**
 * \fn void PutString(const char *s)
 * \brief Ecrit une chaîne de caractères sur la console standard,
 * elle ne permet pas la concaténation dans l'appel de la fonction.
 *eg PutString("ab" + "bc") interdit
 * \param s Chaine de caractère à entrer.
 */
void PutString(const char *s);

/**
 * \fn void GetString(char *s, int n)
 * \brief Obtient une chaîne de caractère de taille maximale définie depuis l'entrée
 * de la console standard. L'utilisateur choisit la taille du buffer de reception.
 * Il choisit donc la taille de la chaine à recuperer
 * \param s Buffer dans lequel les données lues seront écrites, il doit etre initialisé
 * et doit pouvoir contenir n place
 * \param n Corresepond à la taille maximale de la chaine de caracteres
 * Il doit être fixé par l'utilisateur
 */
void GetString(char *s, int n);

/**
 * \fn void PutInt(int n)
 * \brief Ecrit un entier sur la console standard.
 * \param n Entier a écrire sur la console
 */
void PutInt(int n);

/**
 * \fn void GetInt(int * n)
 * \brief Obtient un entier sur 8bits depuis l'entrée de la console standard
 * \param n Entier codé sur 8 bits
 */
void GetInt(int * n);

/**
 * \fn int UserThreadCreate(void f(void *arg), void *arg)
 * \brief Demande la création d'un thread utilisateur au système qui executer la
 * fonction dont le pointeur sera passé en paramètre et qui transmetra a cette
 * fonction l'argument passé en 2nd paramètre (un void *) qui devra etre récuperé
 * comme un void étoile, et casté dans son type d'origine
 * \param f Pointeur vers une fonction à 1 argument (de profil void f (void *) )
 * \param arg Argument à passer a la fonction f, a caster en void*
 * \return Retour le TID du thread créé ou -1 si la création a échouée (Manque de place dans la mémoire etc)
 */
int UserThreadCreate(void f(void *arg), void *arg);

/**
 * \fn void UserThreadExit()
 * \brief Demande la terminaison du thread utilisateur actuel, elle peut etre
 * retardée si d'autres processus sont en création/terminaison, les données du
 * processus seront détruites et son espace mis à disposition pour de nouveaux
 * threads. Si d'autres threads attendent la fin de l'execution de ce thread
 * (UserThreadJoin), ils reprendront peu après l'appel de cette fonction.
 *
 */
void UserThreadExit();

/**
 * \fn void UserThreadJoin(int tid)
 * \brief Attend la terminaison du thread dont le TID est passé en paramètre,
 * si ce thread n'existe pas (Déjà terminé, ou TID n'appartenant a aucun thread),
   la fonction laisse passer l'utilisateur, si un thread
 * essaye de s'attendre lui meme, il passe aussi. Dans les 2 derniers cas, la fonction
 * retourne 1, si l'utilisateur essaye de rejoindre un TID impossible (< 1, donc soit
 *  le thread 0, le thread père, soit un TID négatif), la fonction
 * le laisse passer et retourne -1, enfin, si l'utilisateur peut attendre le thread spécifié
 * comme il le faut, il se met en attente et la fonction retourne 0 lorsque le thread spécifié
 * s'est terminé et que le thread a fini d'attendre.
 *
 * \param tid Thread ID du thread a attendre
 * \return Retourn 1 si le thread n'existe pas ou est le thread actuel, -1 si le
 * TID est impossible et 0 si l'execution s'est déroulée correctement
 *
 */
int UserThreadJoin(int tid);

/**
 * \fn sem_t * UserSemCreate(char * name, int nb)
 * \brief Créer une semaphore de type sem_t et renvoie un pointeur vers elle.
 * Il est necessaire de passer en paramètre un nom ainsi que le nombre de tokens
 * que possède cette semaphore. Cette semaphore devra ensuite être détruite par
 * UserSemDelete.
 * \param name nom de la semaphore, ne doit pas dépasser MAX_SEM_NAME_SIZE caractères
 * \param nb Nombre de token a passer a la sémaphore, doit etre égal ou supérieur
 * a zéro
 * \return Renvoie un pointeur vers la semaphore sem_t
*/
sem_t * UserSemCreate(char * name, int nb);

/**
 * \fn void UserSemP(sem_t * sem)
 * \brief Consome un token de la semaphore ou attend qu'un token soit entré si
 * il n'y en a pas de disponible. Un pointeur vers une sémaphore crée par
 * UserSemCreate doit etre passé en paramètre.
 * \param sem Semaphore qui doit recevoir l'opération P(), doit  crée par UserSemCreate
*/
void UserSemP(sem_t * sem);

/**
 * \fn void UserSemV(sem_t * sem)
 * \brief Poste un token dans la semaphore sem. Un pointeur vers une sémaphore crée par
 * UserSemCreate doit etre passé en paramètre.
 * \param sem Semaphore qui doit recevoir l'opération V(), doit  crée par UserSemCreate
*/
void UserSemV(sem_t * sem);

  /**
   * \fn void UserSemDelete(sem_t * sem);
   * \brief Permet de détruire une sémaphore dont le pointeur est passé en paramètre,
   * il doit pointer vers une sémaphore créer par UserSemCreate.
   * \param sem Semaphore qui doit être détruite, doit  crée par UserSemCreate
  */
void UserSemDelete(sem_t * sem);

/**
 * \fn int ForkExec(char *s)
 * \brief Créer un thread système et lance le programme donné avec le thread crée
 * \param s Le nom du fichier executable à lancer
 */
int ForkExec(char *s);

#define Assert(res)  AssertFull(res, #res, __LINE__, __func__)
void AssertFull(int res, const char* condition, const int lineNumber, const char* functionName);

#endif // IN_USER_MODE

#endif /* SYSCALL_H */
