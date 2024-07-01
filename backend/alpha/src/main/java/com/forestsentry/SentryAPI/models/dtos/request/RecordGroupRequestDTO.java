package com.forestsentry.SentryAPI.models.dtos.request;

import java.util.List;

import jakarta.validation.constraints.NotNull;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class RecordGroupRequestDTO {
    @NotNull
    private List<String> idList;
}