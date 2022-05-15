/**
 * @file roc/config.h
 * @brief Configure options.
*/

#ifndef ROC_CONFIG_H_
#define ROC_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Network port type. */
typedef enum roc_port_type{
    /**
     * Network port for audio source packet.
     * If FEC is not used, this type of port is used to send or receive aduio packets.
     * If FEC is used, this type of port is used to send or receive FEC source pakcets
     * containing audio data plus some FEC headers.
    */
    ROC_PORT_AUDIO_SOURCE = 1,

    /**
     * Network port for audio repair packets.
     * If FEC is used, this type of port is used to send or receive FEC repair packets
     * containing redundant data for audio plus some FEC headers.
    */

    ROC_PORT_AUDIO_REPAIR = 2
}roc_port_type;

/* Network protocol */
typedef enum roc_protocol{
    /* Bare RTP (RFC 3550) */
    ROC_PROTO_RTP = 1,

    /* RTP source packet (RFC 3550) + FECFRAME Reed-Solomon footer (RFC 6865) with m=8. */
    ROC_PROTO_RTP_RS8M_SOURCE = 2,

    /* FEC repair packet + FECFRAME Reed-Solomon header (RFC 6865) with m=8. */
    ROC_PROTO_RS8M_REPAIR = 3,

    /* RTP source packet (RFC 3550) + FECFRAME LDPC-Staircase footer (RFC 6816). */
    ROC_PROTO_RTP_LDPC_SOURCE = 4,

    /* FEC repair packet + FECFRAME LDPC-Staircase header (RFC 6816). */
    ROC_PROTO_LDPC_REPAIR = 5
}roc_protocol;

/* Forward Error Correction Code */
typedef enum roc_fec_code {
    /** 
     * No FEC code. 
     * Compatible with @c ROC_PROTO_RTP protocol .
    */
    ROC_FEC_DISABLE = -1,

   /**
    * Default FEC code.
    * Current default is @c ROC_FEC_RS8M.
   */
    ROC_FEC_DEFAULT = 0,

    /**
     * Reed-Solomon FEC code (RFC 6865) with m=8
     * Good for small block sizes (below 256 packets).
     * Compatible with @c ROC_PROTO_RTP_RS8M_SOURCE and @c ROC_PROTO_RS8M_REPAIR
     * protocol for source and repair ports.
    */
    ROC_FEC_RS8M = 1,

    /**
     * LDPC-Staircase FEC code (RFC 6816)
     * Good for large block sizes (above 1024 packets).
     * Compatible with @c ROC_PROTO_RTP_LDPC_SOURCE and @c ROC_PROTO_LDPC_REPAIR
     * protocols for source and repair ports.
    */
   ROC_FEC_LDPC_STAIRCASE = 2
}roc_fec_code;

/** Packet encoding. */
typedef enum roc_packet_encoding {
    /**
     * PCM signed 16-bits.
     * "L16" encoding from RTP A/V Profile (RFC 3551).
    */
    ROC_PACKET_ENCODING_AVP_L16 = 2
}roc_packet_encoding;

/* Frame encoding */
typedef enum roc_frame_encoding{
    /*PCM flaots*/
    ROC_FRAME_ENCODING_PCM_FLOAT = 1}roc_frame_encoding;

/* Channel set. */
typedef enum roc_channel_set {
    /**
     * Stereo
     * Two channels : left nad right.
    */
    ROC_CHANNEL_SET_STEREO = 2
}roc_channel_set;


/* Resampler profile. */
typedef enum roc_resample_profile {
    /* No resampling. */
    ROC_RESAMPLER_DISABLE = -1,
    
    /**
     * Default profile
     * Current default os @c ROC_RESAMPLER_MEDIUM
    */
    ROC_RESAMPLER_DEFAULT = 0,

    ROC_RESAMPLER_HIGH = 1,

    ROC_RESAMPLER_MEDIUM = 2,

    ROC_RESAMPLER_LOW = 3     
}roc_resample_profile;

/** Context configuration 
 * @see roc_context
*/
typedef struct roc_context_config{
    unsigned int max_packet_size;
    unsigned int max_frame_size;
}roc_context_config;

/**
 * Sender configuration
 * @see roc_sender
*/
typedef struct roc_sender_config
{
    unsigned int frame_sample_rate;
    roc_channel_set frame_channels;
    roc_frame_encoding frame_encoding;
    
    unsigned int packet_sample_rate;
    roc_channel_set packet_channels;
    roc_packet_encoding packet_encoding;
    unsigned long long packet_length;
    unsigned int packet_interleaving;
    unsigned int automatic_timing;
    roc_resample_profile resample_profile;
    roc_fec_code fec_code;
    unsigned int fec_block_source_packets;
    unsigned int fec_block_repair_packets;
}roc_sender_config;

/**
 * Receiver configuration
 * @see roc_receiver
*/
typedef struct roc_receiver_config
{
    unsigned int frame_sample_rate;
    roc_channel_set frame_channels;
    roc_frame_encoding frame_encoding;
    unsigned int automatic_timing;
    roc_resample_profile resample_profile;
    unsigned long long target_latency;
    unsigned long long max_latency_overrun;
    unsigned long long max_latency_underrun;
    long long no_playback_timeout;
    long long broken_playback_timeout;
    unsigned long long breakage_detection_window;
}roc_receiver_config;


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // ROC_CONFIG_H