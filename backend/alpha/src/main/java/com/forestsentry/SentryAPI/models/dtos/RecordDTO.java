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

    public RecordDTO(Float lat, Float lon, Float hum, Float tem, Integer smo, Boolean rai, Integer al, String dev){
        this.latitude = lat;
        this.longitude = lon;
        this.humidity = hum;
        this.temperature = tem;
        this.smokeLevel = smo;
        this.rainStatus = rai;
        this.alertLevel = al;
        this.deviceID = dev;
    }

    public RecordDTO(Record r){
        this.latitude = r.getLatitude();
        this.longitude = r.getLongitude();
        this.humidity = r.getHumidity();
        this.temperature = r.getTemperature();
        this.smokeLevel = r.getSmokeLevel();
        this.rainStatus = r.getRainStatus();
        this.alertLevel = r.getAlertLevel();
        this.deviceID = r.getDeviceID();
        this.timestamp = r.getTimestamp();
    }
}