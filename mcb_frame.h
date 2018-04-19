/**
 * @file mcb_frame.h
 * @brief This file contains useful functions for framing purpose
 *
 * @author  Firmware department
 * @copyright Ingenia Motion Control (c) 2018. All rights reserved.
 */

#ifndef MCB_FRAME_H
#define MCB_FRAME_H

#include <stdint.h>
#include <stdbool.h>

/** Ingenia protocol frame maximum buffer size */
#define MCB_FRM_MAX_DATA_SZ     128U

/** Ingenia protocol frame config buffer header size */
#define MCB_FRM_HEAD_SZ			1U
/** Ingenia protocol frame config buffer size */
#define MCB_FRM_CONFIG_SZ       4U
/** Ingenia protocol frame CRC size */
#define MCB_FRM_CRC_SZ          1U

/** Header position on raw buffer */
#define MCB_FRM_HEAD_IDX        0U
/** Configuration position on raw buffer */
#define MCB_FRM_CONFIG_IDX      1U
/** Cyclic position on raw buffer */
#define MCB_FRM_CYCLIC_IDX      5U

/** Ingenia protocol config function requests/replies */
/** Read request */
#define MCB_REQ_READ            1U
/** Write request */
#define MCB_REQ_WRITE           2U
/** Idle request  */
#define MCB_REQ_IDLE            7U

/** Acknowledge */
#define MCB_REP_ACK             3U
/** Error detected during read */
#define MCB_REP_READ_ERROR      5U
/** Error detected during write */
#define MCB_REP_WRITE_ERROR     6U

/** Ingenia protocol segmentation definitions */
#define MCB_FRM_NOTSEG          0U
#define MCB_FRM_SEG             1U

/** High speed Ingenia protocol frame */
typedef struct {
	/** Data buffer */
	uint16_t u16Buf[MCB_FRM_MAX_DATA_SZ];
    /** Frame size */
	uint16_t u16Sz;
} Mcb_TFrame;

/**
 * Initialises an Ingenia High Speed Protocol frame.
 *
 * @param [out] tFrame
 *      Destination frame
 * @param [in] u16Node
 *      Destination Node.
 * @param [in] u16SubNode
 *      Destination internal network node.
 * @param [in] u16Addr
 *      Destination address.
 * @param [in] u16Cmd
 *      Frame command (request or reply)
 * @param [in] u8Pending
 *      Indicates if the config data will be segmented.
 * @param [in] pCfgBuf
 *      Buffer with config data.
 * @param [in] pCyclicBuf
 *      Buffer with cyclic data.
 * @param [in] szDyn
 *      Size of the cyclic data.
 * @param [in] calcCRC
 * 		Indicates if CRC field will be calculated.
 * @return 0 success, error code otherwise
 */
int32_t
Mcb_FrameCreate(Mcb_TFrame* tFrame, uint16_t u16Addr, uint8_t u8Cmd, uint8_t u8Pending, const void* pCfgBuf,
        const void* pCyclicBuf, uint16_t u16SzCyclic, bool calcCRC);

/**
 * Returns the address of the header.
 *
 * @param [in] tFrame
 *      Input frame.
 * @return Address.
 */
uint16_t
Mcb_FrameGetAddr(const Mcb_TFrame* tFrame);

/**
 * Returns the command (request or reply) of the config data.
 *
 * @param [in] tFrame
 *      Input frame.
 * @return Command.
 */
uint8_t
Mcb_FrameGetCmd(const Mcb_TFrame* tFrame);

/**
 * Checks if the config data is segmented and requires further data.
 *
 * @param [in] tFrame
 *      Input frame.
 * @return true if config data is segmented.
 */
bool
Mcb_FrameGetSegmented(const Mcb_TFrame* tFrame);

/**
 * Returns the config data of a frame.
 *
 * @param [in] tFrame
 *  Input frame.
 * @param [out] pu16Buf
 *  Pointer to config data 
 * @return config data
 */
uint16_t
Mcb_FrameGetConfigData(const Mcb_TFrame* tFrame, uint16_t* pu16Buf);

/**
 * Indicates if the crc for the input frame is correct
 *
 * @param[in] tFrame
 *  Input frame
 *
 * @return true if crc is correct
 *         false if crc is wrong
 */
bool
Mcb_FrameCheckCRC(const Mcb_TFrame* tFrame);

#endif /* MCB_FRAME_H */
