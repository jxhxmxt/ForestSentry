package com.forestsentry.SentryAPI.models.dtos;

import java.sql.Timestamp;

import org.springframework.lang.Nullable;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import jakarta.validation.constraints.NotNull;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class RecordDTO {
    @NotNull
    private Float latitude;

    @NotNull
    private Float longitude;

    @NotNull
    private Float humidity;

    @NotNull
    private Float temperature;

    @NotNull
    private Integer smokeLevel;

    @NotNull
    private Boolean rainStatus;

    @NotNull
    private Integer alertLevel;

    @NotNull
    private String deviceID;

    @Nullable
    private Timestamp timestamp;
}