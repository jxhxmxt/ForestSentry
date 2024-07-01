package com.forestsentry.SentryAPI.models.dtos;

import java.sql.Timestamp;

import org.springframework.lang.Nullable;

import com.forestsentry.SentryAPI.models.entities.Record;

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

    public RecordDTO(Record r){
        this.latitude = r.getLatitude();
        this.longitude = r.getLongitude();
        this.humidity = r.getHumidity();
        this.temperature = r.getTemperature();
        this.smokeLevel = r.getSmokeLevel();
        this.rainStatus = r.getRainStatus();
        this.alertLevel = r.getAlertLevel();
        this.deviceID = r.getDeviceID();
    }
}