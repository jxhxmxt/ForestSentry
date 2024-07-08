package com.forestsentry.SentryAPI.models.entities;

import java.util.UUID;

import com.forestsentry.SentryAPI.models.dtos.RecordDTO;

import java.sql.Timestamp;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.Table;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@Entity
@Table(name = "records", schema = "public")
public class Record {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @Column(name = "id")
    private UUID id;

    @Column(name = "latitude", nullable = false)
    private Float latitude;

    @Column(name = "longitude", nullable = false)
    private Float longitude;

    @Column(name = "humidity", nullable = false)
    private Float humidity;

    @Column(name = "temperature", nullable = false)
    private Float temperature;

    @Column(name = "smoke_level", nullable = false)
    private Integer smokeLevel;

    @Column(name = "rain_status", nullable = false)
    private Boolean rainStatus;

    @Column(name = "alert_level", nullable = false)
    private Integer alertLevel;

    @Column(name = "device_id", nullable = false)
    private String deviceID;

    @Column(name = "timestamp", insertable = false, updatable = false)
    private Timestamp timestamp;

    public Record(Float lat, Float lon, Float hum, Float tem, Integer smo, Boolean rai, Integer al, String dev){
        this.latitude = lat;
        this.longitude = lon;
        this.humidity = hum;
        this.temperature = tem;
        this.smokeLevel = smo;
        this.rainStatus = rai;
        this.alertLevel = al;
        this.deviceID = dev;
    }

    public Record(RecordDTO dto){
        this.latitude = dto.getLatitude();
        this.longitude = dto.getLongitude();
        this.humidity = dto.getHumidity();
        this.temperature = dto.getTemperature();
        this.smokeLevel = dto.getSmokeLevel();
        this.rainStatus = dto.getRainStatus();
        this.alertLevel = dto.getAlertLevel();
        this.deviceID = dto.getDeviceID();
    }

}